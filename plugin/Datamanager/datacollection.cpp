#include "datacollection.h"
//test on vtie kadsjfhkjahf
Datacollection::Datacollection()
{

}

void Datacollection::set_local_cmd(double omega, double linear_speed)
{
    local_cmd[0]=linear_speed;
    local_cmd[1]=omega;

}

#ifdef __linux__
geometry_msgs::Twist Datacollection::send_local_cmd()
{
    geometry_msgs::Twist cmd;
    cmd.linear.x=local_cmd[0];
    cmd.angular.z=local_cmd[1];
    return  cmd;
}
#endif

