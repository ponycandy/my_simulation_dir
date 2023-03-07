#ifndef SINGLE_AGENT_H
#define SINGLE_AGENT_H
#include <Eigen/Core>
#include <QMap>
#include <include/GL_2D/GL2Dcommon.h>
class Single_agent
{
public:
    Single_agent();
    Eigen::MatrixXd state;
    Eigen::MatrixXd act;
    int ID;
    int neib_num;
    int obs_closet_point_num;
    void appendNeibor(Single_agent *neib);
    void remove_all_neibor();
    void remove_all_closepoint();

    void append_closepointpair(int j,pos_xy closest);
    QMap<int,Single_agent*> neib_map;
    QMap<int,pos_xy> closepoint_map;
};

#endif // SINGLE_AGENT_H
