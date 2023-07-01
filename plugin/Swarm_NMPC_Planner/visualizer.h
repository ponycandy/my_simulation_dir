#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QObject>
#include <include/GL_2D/draw_operation.h>
#include <Eigen/Core>
class visualizer : public QObject,public DrawOperation
{
    Q_OBJECT
public:
    explicit visualizer(QObject *parent = nullptr);
    void draw() override;
    void draw_spline(Eigen::MatrixXd var);
    double_t resolution;
signals:

public slots:
    void slot_update_state(Eigen::MatrixXd state_array);

};

#endif // VISUALIZER_H
