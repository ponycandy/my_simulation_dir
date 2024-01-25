#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <QObject>
#include <QThread>
#include <Eigen/Core>
#include <include/GL_2D/ODE_functor.h>
#include <include/GL_2D/GL2Dcommon.h>
#include "service/Tcpcommunicateservice.h"
class Simulator : public QObject,public ODE_functor
{
    Q_OBJECT
public:
    Simulator(QObject *parent = nullptr);
    double roadmodel(double s);
    void ode_function(Eigen::MatrixXd act_mat,Eigen::MatrixXd state_mat) override;
    void control(Eigen::MatrixXd sensor, Eigen::MatrixXd state_mat) override;
    void sensor(Eigen::MatrixXd state_mat) override;

    void broad_cast(Eigen::MatrixXd state_mat, Eigen::MatrixXd act_mat, Eigen::MatrixXd sensor) override;


    double delta_t;

    Eigen::MatrixXd Amat;
    Eigen::MatrixXd Bmat;
    Eigen::MatrixXd Statemat;
    Eigen::MatrixXd controlmat;
    Eigen::MatrixXd feedbackstate;

    Eigen::MatrixXd posstate;



    double mass = 1724;//% kg
    double      g = 9.81;//% N/kg
    double    inertial_z = 1300;//% kg*m^2
    double    l_f = 1.35;//% m
    double       l_r = 1.15;//% m
    double        l_x = l_f + l_r;//% m
    double        h_cg = 0.52;//% m
    double        R_wheel = 0.35;
    double   tau = 0.2;

    //    % tire tramac
    //        % B = 6.8488;
    //    % C = 1.4601;
    //    % D = 1;
    //    % E = -3.6121;

    //    % tire tarmac,wet
    double   B = 11.415;
    double   C = 1.4601;
    double   D = 0.6;
    double   E = -0.20939;

    //    % tire gravel
    //        % B = 15.289;
    //    % C = 1.0901;
    //    % D = 0.6;
    //    % E = 0.86215;
signals:
    void sig_updatepos(Eigen::MatrixXd sig);

};

#endif // SIMULATOR_H
