#include "ClosePoint.h"
ClosePoint::ClosePoint()
{
    edg1.resize(2,1);edg1.setZero();
    edg2.resize(2,1);edg2.setZero();
    pos.resize(2,1);pos.setZero();
    angle=0;
}

void ClosePoint::update_state()
{
    edg1(0,0)=edge1_x;edg1(1,0)=edge1_y;
    edg2(0,0)=edge2_x;edg2(1,0)=edge2_y;
    pos(0,0)=x;
    pos(1,0)=y;
}
