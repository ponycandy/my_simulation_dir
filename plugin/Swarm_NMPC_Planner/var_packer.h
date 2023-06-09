#ifndef VAR_PACKER_H
#define VAR_PACKER_H

#endif // VAR_PACKER_H

#pragma once
#include <Eigen/Core>
#include <PolyParams.h>
#include <xmlcore.h>
#define x_index(pointNum) (5*(pointNum)+0);
#define dx_index(pointNum) (5*(pointNum)+1);
#define y_index(pointNum) (5*(pointNum)+2);
#define dy_index(pointNum) (5*(pointNum)+3);
#define T_index(pointNum) (5*(pointNum)+4);

#define state_x_index(pointNum) (4*pointNum+0);
#define state_y_index(pointNum) (4*pointNum+1);
#define state_vx_index(pointNum) (4*pointNum+2);
#define state_vy_index(pointNum) (4*pointNum+3);

inline void packvariable_pos_set(Eigen::VectorXd &x,PolyParams &sets,int pointnum);
inline void packvariable_states_set(Eigen::VectorXd &x,Eigen::MatrixXd &statemat,
                                    int dec_num);
//注意，这里解包数据的排列顺序是：
//x1dx1Ty1dy1T x1dx1Ty1dy1T，x0为初始变量
void packvariable_pos_set(Eigen::VectorXd &x,PolyParams &sets,int pointnum)
{
    //这里的bug，需要考虑初始时刻的x0x1,dx0,dx1值不是从params里面获取的
    //也就是存在一组这样的异常值，它们初始的决定了给与的动作变量
    //变量的排列顺序：x1dx1y1dy1x2dx2y2dy2T....考虑初始状态的x0从外部读取
    for(int i=0;i<pointnum;i++)
    {
        if(i>0)
        {
            int dm=0;
            sets.Spline_Set.value(dm).value(i).x0=x(x_index(i-1));
            sets.Spline_Set.value(dm).value(i).x1=x(x_index(i));
            sets.Spline_Set.value(dm).value(i).dx0=x(dx_index(i-1));
            sets.Spline_Set.value(dm).value(i).dx1=x(dx_index(i));
            sets.Spline_Set.value(dm).value(i).lasting_time=x(T_index(i));
            sets.Spline_Set.value(dm).value(i).total_phase_num=pointnum;

            dm=1;
            sets.Spline_Set.value(dm).value(i).x0=x(y_index(i-1));
            sets.Spline_Set.value(dm).value(i).x1=x(y_index(i));
            sets.Spline_Set.value(dm).value(i).dx0=x(dy_index(i-1));
            sets.Spline_Set.value(dm).value(i).dx1=x(dy_index(i));
            sets.Spline_Set.value(dm).value(i).lasting_time=x(T_index(i));
            sets.Spline_Set.value(dm).value(i).total_phase_num=pointnum;
        }
        else
        {
            //初始数据解包略有不同
            xmlCore xmlreader("initialparams.xml");
            double x0=xmlreader.xmlRead("x0");
            double y0=xmlreader.xmlRead("y0");
            double vx=xmlreader.xmlRead("vx");
            double vy=xmlreader.xmlRead("vy");
            int dm=0;
            sets.Spline_Set.value(dm).value(i).x0=x0;
            sets.Spline_Set.value(dm).value(i).x1=x(0);
            sets.Spline_Set.value(dm).value(i).dx0=vx;
            sets.Spline_Set.value(dm).value(i).dx1=x(1);
            sets.Spline_Set.value(dm).value(i).lasting_time=x(4);
            sets.Spline_Set.value(dm).value(i).total_phase_num=pointnum;

            dm=1;
            sets.Spline_Set.value(dm).value(i).x0=y0;
            sets.Spline_Set.value(dm).value(i).x1=x(2);
            sets.Spline_Set.value(dm).value(i).dx0=vy;
            sets.Spline_Set.value(dm).value(i).dx1=x(3);
            sets.Spline_Set.value(dm).value(i).lasting_time=x(4);
            sets.Spline_Set.value(dm).value(i).total_phase_num=pointnum;

        }
    }
    sets.rearrange();
}
void packvariable_states_set(Eigen::VectorXd &x,Eigen::MatrixXd &statemat,
                             int dec_num)
{
    for(int i=0;i<dec_num;i++)
    {
        statemat(0,i)=x(state_x_index(i));
        statemat(1,i)=x(state_y_index(i));
        statemat(2,i)=x(state_vx_index(i));
        statemat(3,i)=x(state_vy_index(i));
    }
}
