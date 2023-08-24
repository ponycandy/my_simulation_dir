#include "collisioncalculator.h"
#include "QPolygonF"
#include "CollisionDetectActivator.h"
collisionCalculator::collisionCalculator(QObject *parent) : QObject(parent)
{
    CollisionDetectActivator::registerservice(this,"CollisionDetectservice");
}

collison_result collisionCalculator::polygen_circle_detect(double circle_x, double circle_y, double r, QPolygonF obs)
{
    int head;int tail;
    Eigen::MatrixXd edge;edge.resize(2,1);edge.setZero();
    Eigen::MatrixXd edge1;edge1.resize(2,1);edge1.setZero();
    Eigen::MatrixXd edge2;edge2.resize(2,1);edge2.setZero();

    Eigen::MatrixXd prj_edge;prj_edge.resize(2,1);prj_edge.setZero();
    Eigen::MatrixXd distance;distance.resize(obs.length(),1);

    collison_result result;

    for(int i=1;i<=obs.length();i++)
    {
        head=i;
        tail=(i+1)%obs.length();
        if(tail==0)
        {
            tail=obs.length();
        }

        edge(0,0)=obs.at(tail-1).x()-obs.at(head-1).x();
        edge(1,0)=obs.at(tail-1).y()-obs.at(head-1).y();

        distance(i-1,0)=pow((obs.at(head-1).x()-circle_x),2)
                +pow((obs.at(head-1).y()-circle_y),2);


        prj_edge(0,0)=-edge(1,0);
        prj_edge(1,0)=edge(0,0);
        prj_range circle=circle_projection(circle_x,circle_y,r,prj_edge);
        prj_range convex=convex_projection(obs,prj_edge);
        if(circle.x_min>convex.x_max || circle.x_max<convex.x_min) //未相交
        {
            result.flag=0;
            result.closest_point.x=0;
            result.closest_point.y=0;
            return result;
        }
        else
        {

        }
    }//circle_projection

    double iter;
    int index=0;
    iter=distance(0,0);
    for(int i=1;i<obs.length();i++)
    {
        if(iter<distance(i,0))
        {

        }
        else
        {
            iter=distance(i,0);
            index=i;
        }
    }//now index +1 hold the id of nearesi_vertex point
    index+=1;
    head=index;
    int former=index-1;

    int latter=(index+1)%obs.length();
    if(former<=0)
    {
        former=obs.length();
    }
    if(latter==0)
    {
        latter=obs.length();
    }
    edge(0,0)=-(circle_x-obs.at(head-1).x());
    edge(1,0)=-(circle_y-obs.at(head-1).y());

    edge1(0,0)=(obs.at(former-1).x()-obs.at(head-1).x());
    edge1(1,0)=(obs.at(former-1).y()-obs.at(head-1).y());

    edge2(0,0)=(obs.at(latter-1).x()-obs.at(head-1).x());
    edge2(1,0)=(obs.at(latter-1).y()-obs.at(head-1).y());

    prj_edge(0,0)=-edge(1,0);
    prj_edge(1,0)=edge(0,0);
    prj_edge.normalize();
    prj_range circle=circle_projection(circle_x,circle_y,r,prj_edge);
    prj_range convex=convex_projection(obs,prj_edge);
    if(circle.x_min>convex.x_max || circle.x_max<convex.x_min) //未相交
    {
        result.flag=0;
        result.closest_point.x=0;
        result.closest_point.y=0;
        return result;
    }
    else
    {
        result.flag=1;
        double x0,y0,x1,y1,x2,y2;
//        result.closest_point.pos.resize(2,1);
        if(vector_dot(edge2,edge1)>=0)
        {
            if(vector_dot(edge,edge1)>0 && vector_dot(edge,edge2)>0)
            {
                result.closest_point.x=obs.at(index-1).x();
                result.closest_point.y=obs.at(index-1).y();
                result.closest_point.last_vertex=former;
                result.closest_point.next_vertex=latter;
                result.closest_point.edge1_x=edge1(0,0);result.closest_point.edge1_y=edge1(1,0);
                result.closest_point.edge2_x=edge2(0,0);result.closest_point.edge2_y=edge2(1,0);
//                result.closest_point.edg1=edge1;
//                result.closest_point.edg2=edge2;
                return result;
            }
            if(vector_dot(edge,edge1)<0 && vector_dot(edge,edge2)>0)
            {
                x0=edge1(0,0);y0=edge1(1,0);x1=obs.at(index-1).x();y1=obs.at(index-1).y();
                x2=circle_x;y2=circle_y;

                result.closest_point.x=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(y2-y1)+pow(y0,2)*x1+pow(x0,2)*x2);
                result.closest_point.y=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(x2-x1)+pow(y0,2)*y2+pow(x0,2)*y1);
                result.closest_point.last_vertex=former;
                result.closest_point.next_vertex=index;
                result.closest_point.edge1_x=edge1(0,0);result.closest_point.edge1_y=edge1(1,0);
                result.closest_point.edge2_x=-edge1(0,0);result.closest_point.edge2_y=-edge1(1,0);
//                result.closest_point.edg1=edge1;
//                result.closest_point.edg2=-edge1;


                return result;
            }
            if(vector_dot(edge,edge1)>0 && vector_dot(edge,edge2)<0)
            {
                x0=edge2(0,0);y0=edge2(1,0);x1=obs.at(index-1).x();y1=obs.at(index-1).y();
                x2=circle_x;y2=circle_y;

                result.closest_point.x=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(y2-y1)+pow(y0,2)*x1+pow(x0,2)*x2);
                result.closest_point.y=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(x2-x1)+pow(y0,2)*y2+pow(x0,2)*y1);
                result.closest_point.last_vertex=index;
                result.closest_point.next_vertex=latter;
                 result.closest_point.edge1_x=edge2(0,0);result.closest_point.edge1_y=edge2(1,0);
                 result.closest_point.edge2_x=-edge2(0,0);result.closest_point.edge2_y=-edge2(1,0);

//                result.closest_point.edg1=edge2;
//                result.closest_point.edg2=-edge2;
                return result;
            }
            if(vector_dot(edge,edge1)<0 && vector_dot(edge,edge2)<0)
            {
                x0=edge1(0,0);y0=edge1(1,0);x1=obs.at(index-1).x();y1=obs.at(index-1).y();
                x2=circle_x;y2=circle_y;

                double x01=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(y2-y1)+pow(y0,2)*x1+pow(x0,2)*x2);
                double y01=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(x2-x1)+pow(y0,2)*y2+pow(x0,2)*y1);

                x0=edge2(0,0);y0=edge2(1,0);x1=obs.at(index-1).x();y1=obs.at(index-1).y();
                x2=circle_x;y2=circle_y;

                double x02=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(y2-y1)+pow(y0,2)*x1+pow(x0,2)*x2);
                double y02=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(x2-x1)+pow(y0,2)*y2+pow(x0,2)*y1);

                double dis_1=pow(x01-x1,2)+pow(y01-y1,2);
                double dis_2=pow(x02-x1,2)+pow(y02-y1,2);
                if(dis_2<dis_1)
                {
                    result.closest_point.x=x01;
                    result.closest_point.y=y01;
                    result.closest_point.last_vertex=former;
                    result.closest_point.next_vertex=index;
                    result.closest_point.edge1_x=edge1(0,0);result.closest_point.edge1_y=edge1(1,0);
                    result.closest_point.edge2_x=-edge1(0,0);result.closest_point.edge2_y=-edge1(1,0);
//                    result.closest_point.edg1=edge1;
//                    result.closest_point.edg2=-edge1;

                }
                else
                {
                    result.closest_point.x=x02;
                    result.closest_point.y=y02;
                    result.closest_point.last_vertex=index;
                    result.closest_point.next_vertex=latter;
                    result.closest_point.edge1_x=edge2(0,0);result.closest_point.edge1_y=edge2(1,0);
                    result.closest_point.edge2_x=-edge2(0,0);result.closest_point.edge2_y=-edge2(1,0);

                }
                return result;
            }
        }
        else
        {
            if(vector_dot(edge,edge1)>0 && vector_dot(edge,edge2)>0)
            {
                result.closest_point.x=obs.at(index-1).x();
                result.closest_point.y=obs.at(index-1).y();
                result.closest_point.last_vertex=former;
                result.closest_point.next_vertex=latter;
                result.closest_point.edge1_x=edge1(0,0);result.closest_point.edge1_y=edge1(1,0);
                result.closest_point.edge2_x=edge2(0,0);result.closest_point.edge2_y=edge2(1,0);

                return result;
            }
            if(vector_dot(edge,edge1)<0 && vector_dot(edge,edge2)>0)
            {
                x0=edge1(0,0);y0=edge1(1,0);x1=obs.at(index-1).x();y1=obs.at(index-1).y();
                x2=circle_x;y2=circle_y;

                result.closest_point.x=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(y2-y1)+pow(y0,2)*x1+pow(x0,2)*x2);
                result.closest_point.y=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(x2-x1)+pow(y0,2)*y2+pow(x0,2)*y1);
                result.closest_point.last_vertex=former;
                result.closest_point.next_vertex=index;
                result.closest_point.edge1_x=edge1(0,0);result.closest_point.edge1_y=edge1(1,0);
                result.closest_point.edge2_x=-edge1(0,0);result.closest_point.edge2_y=-edge1(1,0);
                //                result.closest_point.edg1=edge1;
                //                result.closest_point.edg2=-edge1;


                return result;
            }
            if(vector_dot(edge,edge1)>0 && vector_dot(edge,edge2)<0)
            {
                x0=edge2(0,0);y0=edge2(1,0);x1=obs.at(index-1).x();y1=obs.at(index-1).y();
                x2=circle_x;y2=circle_y;

                result.closest_point.x=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(y2-y1)+pow(y0,2)*x1+pow(x0,2)*x2);
                result.closest_point.y=(1/(pow(x0,2)+pow(y0,2)))*(x0*y0*(x2-x1)+pow(y0,2)*y2+pow(x0,2)*y1);
                result.closest_point.last_vertex=index;
                result.closest_point.next_vertex=latter;
                result.closest_point.edge1_x=edge2(0,0);result.closest_point.edge1_y=edge2(1,0);
                result.closest_point.edge2_x=-edge2(0,0);result.closest_point.edge2_y=-edge2(1,0);

                //                result.closest_point.edg1=edge2;
                //                result.closest_point.edg2=-edge2;
                return result;
            }
        }
    }



}

collison_result2 collisionCalculator::polygen_line_segment_detect(Eigen::MatrixXd &Point_a0, Eigen::MatrixXd &Point_a1, QPolygonF &obs)
{
//遍历所有的边，依次执行交叉检测算法，理论上最多有两次交叉,为了通用性
 //需要返回所有交叉的边的头尾以及交叉点，



    //直接计算交点是否存在会比较快

    Eigen::MatrixXd E_1=Point_a0-Point_a1;

    Eigen::MatrixXd prj_edge;prj_edge.resize(2,1);prj_edge.setZero();

    Eigen::MatrixXd p_on_line_1;p_on_line_1=prj_edge;
    Eigen::MatrixXd p_on_line_2;p_on_line_2=prj_edge;  //2是大，1是小
    Eigen::MatrixXd p_1;p_1=prj_edge; //2是大，1是小
    Eigen::MatrixXd p_2;p_2=prj_edge;
    if(Point_a0(0,0)>Point_a1(0,0))
    {
        p_2=Point_a0;
        p_1=Point_a1;
    }
    else
    {
        p_1=Point_a0;
        p_2=Point_a1;
    }
    Eigen::MatrixXd midmat;
    midmat.resize(2,2);
    int head;int tail;
    Eigen::MatrixXd edge;edge.resize(2,1);edge.setZero();





    collison_result2 result;
    result.flag=0;
    result.collisionnum=0;

    for(int i=1;i<=obs.length();i++)
    {
        head=i;
        tail=(i+1)%obs.length();
        if(tail==0)
        {
            tail=obs.length();
        }

        edge(0,0)=obs.at(tail-1).x()-obs.at(head-1).x();
        edge(1,0)=obs.at(tail-1).y()-obs.at(head-1).y();

        if(obs.at(head-1).x()>obs.at(tail-1).x())

        {
            p_on_line_2<<obs.at(head-1).x(),obs.at(head-1).y();
            p_on_line_1<<obs.at(tail-1).x(),obs.at(tail-1).y();
        }
        else
        {
            p_on_line_1<<obs.at(head-1).x(),obs.at(head-1).y();
            p_on_line_2<<obs.at(tail-1).x(),obs.at(tail-1).y();
        }

        midmat<<E_1(0,0),edge(0,0),
            E_1(1,0),edge(1,0);
        double value= midmat.determinant();
        //直线参数:E=edge,p=[obs.at(head-1).x(),obs.at(head-1).y()]
        if(value==0)//平行于一条边,那就是和这条边无交点
        {

        }
        else
        {
            prj_edge=midmat.inverse()*(p_on_line_1-p_1);
            value=prj_edge(0,0);
            prj_edge=p_1+value*E_1;//交点坐标,该交点肯定在E1上
            //如果交点既在线段1，又在线段2上，那就相交：
            if(prj_edge(0,0)>p_1(0,0) && prj_edge(0,0)<p_2(0,0) &&
                prj_edge(0,0)>p_on_line_1(0,0) && prj_edge(0,0)<p_on_line_2(0,0) )
            {
                //那就是有碰撞了:
                result.flag=1;
                result.collisionnum+=1;
                pos_xy clresult;
                clresult.obs_ID=-1;
                clresult.x=prj_edge(0,0);clresult.y=prj_edge(1,0);
                clresult.edge1_x=p_on_line_1(0,0);clresult.edge1_y=p_on_line_1(1,0);
                clresult.edge2_x=p_on_line_2(0,0);clresult.edge2_y=p_on_line_2(1,0);
                result.collision.push_back(clresult);
            }
        }


    }
//等一下，我觉得按照SAT的算法似乎没有比直接遍历快，实际上投影
    //计算的复杂度已经足够搞出相交点了
    return result;
}

prj_range collisionCalculator::circle_projection(double circlex, double circley, double r, Eigen::MatrixXd vec)
{
    prj_range range;
    Eigen::MatrixXd pos;pos.resize(2,1);
    pos<< circlex,
            circley;
    double origin=pos(0,0)*vec(0,0)+pos(1,0)*vec(1,0);
    //此处vec已经标准化了
//    double norm=sqrt(pow(vec(0,0),2)+pow(vec(1,0),2));
    range.x_max=origin+r; //这里为啥要加这个来着？当时我为啥删掉注释来着...
    range.x_min=origin-r;//不对啊，为什么r要乘以norm啊
    //我们把norm删掉试试看...
    if(range.x_max<range.x_min)
    {
        origin=range.x_max;
        range.x_max=range.x_min;
        range.x_min=origin;
    }
    return range;
}

prj_range collisionCalculator::convex_projection(QPolygonF obs, Eigen::MatrixXd vec)
{
    Eigen::MatrixXd edge;edge.resize(2,1);edge.setZero();
    Eigen::MatrixXd distance;distance.resize(obs.length(),1);

    prj_range range;
    range.x_max=0;
    range.x_min=0;
    double origin=0;
    for(int i=1;i<=obs.length();i++)
    {
        edge(0,0)=obs.at(i-1).x();
        edge(1,0)=obs.at(i-1).y();


        origin=edge(0,0)*vec(0,0)+edge(1,0)*vec(1,0);
        distance(i-1,0)=origin;

    }
    range.x_min=find_min(distance,obs.length());
    range.x_max=find_max(distance,obs.length());
    return range;
}

prj_range collisionCalculator::Line_projection(double startx, double starty, double endx, double endy, Eigen::MatrixXd vec)
{
    prj_range range;
    range.x_max=startx*vec(0,0)+starty*vec(1,0);
    range.x_min=endx*vec(0,0)+endy*vec(1,0);
    double origin;
    if(range.x_max<range.x_min)
    {
        origin=range.x_max;
        range.x_max=range.x_min;
        range.x_min=origin;
    }
    return range;
}

double collisionCalculator::find_min(Eigen::MatrixXd dis, int num)
{
    double iter;
    int index=0;
    iter=dis(0,0);
    for(int i=1;i<num;i++)
    {
        if(iter<dis(i,0))
        {

        }
        else
        {
            iter=dis(i,0);
            index=i;
        }
    }
    return  iter;
}

double collisionCalculator::find_max(Eigen::MatrixXd dis, int num)
{
    double iter;
    int index=0;
    iter=dis(0,0);
    for(int i=1;i<num;i++)
    {
        if(iter>dis(i,0))
        {

        }
        else
        {
            iter=dis(i,0);
            index=i;
        }
    }
    return  iter;
}

double collisionCalculator::vector_dot(Eigen::MatrixXd ad, Eigen::MatrixXd bd)
{
    double cd=ad(0,0)*bd(0,0)+ad(1,0)*bd(1,0);
    return  cd;
}
