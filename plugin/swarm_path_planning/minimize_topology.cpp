#include "minimize_topology.h"
#include "swarm_path_planningActivator.h"

minimize_Topology::minimize_Topology(std::string name):ifopt::CostTerm(name)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");
    //    obspos<<7.5,12; //这里定义障碍物的位置，实际上因为存在多个障碍物
    //我们是需要更改代码去适配的，这就是下午的工作
    xmlreader.xmlRead("agent_num",agentnum);
    xmlreader.xmlRead("Incp",Incp);
    xmlreader.xmlRead("decnum",decnum);
    xmlreader.xmlRead("collision_r",collision_r);
    xmlreader.xmlRead("communication_range",communication_range);


    common_initialize(var_struct);
    initilize_Traj(Target_Traj);
    actMat.resize(2*agentnum,decnum);
    stateMat.resize(3*agentnum,decnum);
    m_jac.resize(1,5*agentnum*decnum);
    m_Hession.resize(5*agentnum*decnum,5*agentnum*decnum);
    readconfig("./config/swarmmpc/swarm.xml");
    m_service=swarm_path_planningActivator::getService<CollisionDetectservice>("CollisionDetectservice");
}

void minimize_Topology::readconfig(QString filename)
{
    xmlCore xmlreader("./config/swarmmpc/swarm.xml");
    xmlreader.xmlRead("obs_num",obs_num);

    Eigen::MatrixXd obs_mat;

    for(int i=1;i<=obs_num;i++)
    {
        SwarmObstacle *new_obs=new SwarmObstacle;
        QString obs_term_name="OBS_"+QString::number(i)+"_vertexnum";
        xmlreader.xmlRead(obs_term_name.toStdString(),new_obs->vertex_num);
        new_obs->ID=i;
        obs_mat.resize(new_obs->vertex_num,2);
        obs_term_name="OBS_"+QString::number(i)+"_vertexparams";
        std::vector<double> point_x_vec;
        std::vector<double> point_y_vec;
        xmlreader.xmlRead(obs_term_name.toStdString(),obs_mat);
        for(int j=1;j<=new_obs->vertex_num;j=j+1)
        {
            double x= obs_mat(j-1,0);
            double y= obs_mat(j-1,1);
            point_x_vec.push_back(x);
            point_y_vec.push_back(y);
            new_obs->vertex_map<<QPointF(x,y);
        }

        double max_x = *max_element(point_x_vec.begin(), point_x_vec.end());
        double max_y = *max_element(point_y_vec.begin(), point_y_vec.end());
        double min_x = *min_element(point_x_vec.begin(), point_x_vec.end());
        double min_y = *min_element(point_y_vec.begin(), point_y_vec.end());
        double communication_range=0;
        double collision_r=0;

        xmlreader.xmlRead("communication_range",communication_range);
        xmlreader.xmlRead("collision_r",collision_r);

        new_obs->x_up=max_x+collision_r;
        new_obs->x_low=min_x-collision_r;
        new_obs->y_up=max_y+collision_r;
        new_obs->y_low=min_y-collision_r;

        obsbounding_group.insert(i,new_obs);
    }
}

double minimize_Topology::GetCost() const
{
    VectorXd x = GetVariables()->GetComponent("action_state_set1")->GetValues();
    m_jac.setZero();
    m_Hession.setZero();
    //这才是组队距离
//我们需要修正所有由于omega位置错误连带的外部错误
    unpackvariable(x,5*agentnum,decnum,2*agentnum,3*agentnum,agentnum,actMat,stateMat,var_struct);
    double error=0;
    double koef=100*agentnum*decnum;
    for(int steps=0;steps<decnum;steps++)
    {
        for(int i=0;i<agentnum;i++)
        {
            //agent_num最后一个agent是leader需要追踪预测出来的目标轨迹
            if(i!=agentnum-1)
            {
                int edge_num=(var_struct.steps[steps])->agents[i]->edgenum;
                for(int j=0;j<edge_num;j++)
                {
                    int ID=var_struct.steps[steps]->agents[i]->Edg[j]->End_Node_ID;
                    double length=var_struct.steps[steps]->agents[i]->Edg[j]->length;
                    single_vehicle_data *neib=var_struct.steps[steps]->agents[ID-1];
                    double Dis=pow((var_struct.steps[steps]->agents[i]->posxy-neib->posxy).norm(),2)-length*length;
                    double xi=var_struct.steps[steps]->agents[i]->posxy(0,0);
                    double yi=var_struct.steps[steps]->agents[i]->posxy(1,0);
                    double xj=neib->posxy(0,0);
                    double yj=neib->posxy(1,0);
                    error+=(Dis*Dis)/(koef);

                    m_jac(0,var_struct.steps[steps]->agents[i]->indexofx)+=4*Dis*((var_struct.steps[steps])->agents[i]->x-neib->x)/(koef);
                    m_jac(0,var_struct.steps[steps]->agents[i]->indexofy)+=4*Dis*((var_struct.steps[steps])->agents[i]->y-neib->y)/(koef);
                    m_jac(0,var_struct.steps[steps]->agents[ID-1]->indexofx)+=4*Dis*(-(var_struct.steps[steps])->agents[i]->x+neib->x)/(koef);
                    m_jac(0,var_struct.steps[steps]->agents[ID-1]->indexofy)+=4*Dis*(-(var_struct.steps[steps])->agents[i]->y+neib->y)/(koef);
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 var_struct.steps[steps]->agents[i]->indexofx,
                                 2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 neib->indexofx,
                                 2/koef*(-4*(xi-xj)*(xi-xj)-2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[ID-1]->indexofx,
                                 var_struct.steps[steps]->agents[ID-1]->indexofx,
                                 2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));

                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofy,
                                 var_struct.steps[steps]->agents[i]->indexofy,
                                 2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofy,
                                 var_struct.steps[steps]->agents[ID-1]->indexofy,
                                 2/koef*(-4*(yi-yj)*(yi-yj)-2*Dis));
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[ID-1]->indexofy,
                                 var_struct.steps[steps]->agents[ID-1]->indexofy,
                                 2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));

                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 neib->indexofy,
                                 2/koef*(4*(xi-xj)*(yj-yi))); //xiyj
                    fillsymetrix(m_Hession,var_struct.steps[steps]->agents[i]->indexofx,
                                 var_struct.steps[steps]->agents[i]->indexofy,
                                 2/koef*(4*(xi-xj)*(yi-yj)));//xiyi
                    fillsymetrix(m_Hession,neib->indexofx,
                                 neib->indexofy,
                                 2/koef*(4*(xj-xi)*(yj-yi)));//xjyj
                    fillsymetrix(m_Hession,neib->indexofx,
                                 var_struct.steps[steps]->agents[i]->indexofy,
                                 2/koef*(4*(xj-xi)*(yi-yj)));//xjyi
                    //it's really error prone!
                }
            }
            else
            {
                //注意，最后一个是leader，我们减小的是leader到目标的距离！！
                single_vehicle_data *leader=var_struct.steps[steps]->agents[i];
                Eigen::Vector2d postarget=Target_Traj[steps];
                double Dis=pow((var_struct.steps[steps]->agents[i]->posxy-postarget).norm(),2)-Incp*Incp;
                double xi=leader->posxy(0,0);
                double yi=leader->posxy(1,0);
                double xj=postarget(0,0);
                double yj=postarget(1,0);
                error+=(Dis*Dis)/(koef);

                m_jac(0,leader->indexofx)+=4*Dis*((xi-xj)/(koef));
                m_jac(0,leader->indexofy)+=4*Dis*((yi-yj)/(koef));

                //xixi
                fillsymetrix(m_Hession,leader->indexofx,
                             leader->indexofx,
                             2/koef*(4*(xi-xj)*(xi-xj)+2*Dis));
                //yiyi
                fillsymetrix(m_Hession,leader->indexofy,
                             leader->indexofy,
                             2/koef*(4*(yi-yj)*(yi-yj)+2*Dis));

                //xiyi
                fillsymetrix(m_Hession,leader->indexofx,
                             leader->indexofy,
                             2/koef*(4*(xi-xj)*(yi-yj)));//xiyi

                //作为leader的目标是减小和目标物体轨迹的差距
            }
            //下面添加对障碍物避障的最小项
            //有一个想法，可以试一试
            //计算距离当前物体的最近点，然后将
            //这个点的坐标赋予obspos
            //如果最近点不存在，那么就将z项置100,取消掉error的加值
            for(int iobs=1;iobs<=obs_num;iobs++)
            {
                SwarmObstacle *obs=obsbounding_group.value(iobs);
                single_vehicle_data *agent=(var_struct.steps[steps])->agents[i];
                collison_result result=m_service->polygen_circle_detect(agent->posxy(0,0),
                                                                          agent->posxy(1,0),collision_r,obs->vertex_map);
//好的，非常显然，如果我们执意不使用圆，而使用多边形进行躲避
                //挂掉的可能性非常大
                //我们又不想把这个问题变成non-convex的
                //所以很麻烦
                if (result.flag==1)
                {
                    obspos<<result.closest_point.x,result.closest_point.y;
                    double z=pow((agent->posxy-obspos).norm()/collision_r,2);
                    double first,second;

                    //            potential+=(PotentialCalc(z,first,second));

                    error+=(20*PotentialCalc(z,first,second));

                    double Dzdx=2/(collision_r*collision_r)*(agent->x-obspos(0,0));
                    double Dzdy=2/(collision_r*collision_r)*(agent->y-obspos(1,0));

                    m_jac(0,agent->indexofx)+=20*first*Dzdx;
                    m_jac(0,agent->indexofy)+=20*first*Dzdy;
                    if(z<1)
                    {
                        double valuex =
                            -6/(collision_r*collision_r)*(z-1)*
                            (4/(collision_r*collision_r)*pow(agent->x-obspos(0,0),2)
                             +(z-1));
                        double valuey =
                            -6/(collision_r*collision_r)*(z-1)*
                            (4/(collision_r*collision_r)*pow(agent->y-obspos(1,0),2)
                             +(z-1));
                        double valuexy =-24/(pow(collision_r,4))*
                                         (z-1)*(agent->y-obspos(1,0))*(agent->x-obspos(0,0));
                        fillsymetrix(m_Hession,agent->indexofx,agent->indexofx,
                                     20*valuex);
                        fillsymetrix(m_Hession,agent->indexofy,agent->indexofy,
                                     20*valuey);
                        fillsymetrix(m_Hession,agent->indexofx,agent->indexofy,
                                     20*valuexy);
                        //他们是连续的
                    }
                    //上面添加对障碍物避障的最小项
                }
                else
                {

                }
            }
        }


    }
    //碰撞约束完成,雅可比计算相对比较简单，就不用Tensor了
    return error;
}

void minimize_Topology::FillHessionBlock(std::string var_set, Jacobian &jac_block, int irow) const
{
    GetCost();
    jac_block=m_Hession.sparseView();
//    std::cout<<jac_block<<std::endl;
}

void minimize_Topology::FillJacobianBlock(std::string var_set, Jacobian &jac) const
{
    GetCost();
    jac=m_jac.sparseView();
//    std::cout<<jac<<std::endl;

}

