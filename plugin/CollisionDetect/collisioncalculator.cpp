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
                result.closest_point.last_vertex=index;
                result.closest_point.next_vertex=former;
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
                    result.closest_point.last_vertex=index;
                    result.closest_point.next_vertex=former;
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
//                    result.closest_point.edg1=edge2;
//                    result.closest_point.edg2=-edge2;
                }
                return result;
            }
        }
    }



}

prj_range collisionCalculator::circle_projection(double circlex, double circley, double r, Eigen::MatrixXd vec)
{
    prj_range range;
    Eigen::MatrixXd pos;pos.resize(2,1);
    pos<< circlex,
            circley;
    double origin=pos(0,0)*vec(0,0)+pos(1,0)*vec(1,0);
    double norm=sqrt(pow(vec(0,0),2)+pow(vec(1,0),2));
    range.x_max=origin+r*norm;
    range.x_min=origin-r*norm;
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
