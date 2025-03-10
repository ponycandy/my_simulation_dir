#include "collisioncalculator.h"
#include "QPolygonF"
#include "CollisionDetectActivator.h"
#include <QDebug>
collisionCalculator::collisionCalculator(QObject *parent) : QObject(parent)
{
    CollisionDetectActivator::registerservice(this,"CollisionDetectservice");
}

collison_result collisionCalculator::polygen_circle_detect(double circle_x, double circle_y, double r, QPolygonF obs)
{
    QPointF nearest_point;
    Eigen::MatrixXd ed1;ed1.resize(2,1);
    Eigen::MatrixXd ed2=ed1;
    double min_dist_sq = std::numeric_limits<double>::max();
    int index=0;
    int n = obs.size();
    for (int i = 0; i < n; ++i) {
        // 获取当前边的两个端点
        QPointF A = obs[i];
        QPointF B = obs[(i+1)%n];

        // 计算向量AB和AP
        double ax = A.x();
        double ay = A.y();
        double bx = B.x();
        double by = B.y();
        double abx = bx - ax;
        double aby = by - ay;
        double apx = circle_x - ax;
        double apy = circle_y - ay;

        // 计算投影参数t
        double dot = apx * abx + apy * aby;
        double ab_length_sq = abx * abx + aby * aby;
        double t = ab_length_sq > 0 ? dot / ab_length_sq : 0.0;

        // 约束t到[0,1]区间
        t = std::max(0.0, std::min(1.0, t));

        // 计算最近点坐标
        double nearest_x = ax + t * abx;
        double nearest_y = ay + t * aby;

        // 计算距离平方
        double dx = circle_x - nearest_x;
        double dy = circle_y - nearest_y;
        double dist_sq = dx * dx + dy * dy;

        // 更新最近点信息
        if (dist_sq <= min_dist_sq) {
            min_dist_sq = dist_sq;
            nearest_point.setX(nearest_x);
            nearest_point.setY(nearest_y);
            index=i;
            //在此处计算边
            //            if(nearest_x==ax && nearest_y==ay)
            //            {

            //            }
        }
    }

    // 计算最终碰撞结果
    bool collided = std::sqrt(min_dist_sq) <= r;
    collison_result res;
    if(collided==false)
    {
        res.flag=0;
        res.closest_point.x=0;
        res.closest_point.y=0;
    }
    else
    {
        res.flag=1;
        res.closest_point.x=nearest_point.x();
        res.closest_point.y=nearest_point.y();

        QPointF A = obs[index];
        QPointF B = obs[(index+1)%n];
        index=index-1;
        if(index<0)
        {
            index=obs.length()-1;
        }
        QPointF C = obs[index];

        // 计算向量AB和AP
        double ax = A.x();
        double ay = A.y();
        double bx = B.x();
        double by = B.y();

        if(nearest_point.x()==ax && nearest_point.y()==ay)
        {
            //顶点
            ed1<<C.x()-ax,C.y()-ay;
            ed2<<B.x()-ax,B.y()-ay;
            ed1.normalize();
            ed2.normalize();
        }
        else
        {
            //边
            ed2<<B.x()-ax,B.y()-ay;
            ed1=-ed2;
            ed1.normalize();
            ed2.normalize();
        }

        res.closest_point.next_vertex=1;
        res.closest_point.last_vertex=1;
        res.closest_point.edge1_x=ed1(0,0);
        res.closest_point.edge1_y=ed1(1,0);
        res.closest_point.edge2_x=ed2(0,0);
        res.closest_point.edge2_y=ed2(1,0);
    }
    return res;



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
