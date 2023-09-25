#ifndef CPYDEVODER_H
#define CPYDEVODER_H

#include <QObject>
#include <defines/CpyDefines.h>
#include <Eigen/Core>
#include <service/CPYcoderservice.h>
#include <service/Tcpcommunicateservice.h>
#include <service/TCPserverservice.h>

class CPyDevoder : public QObject,public CPYcoderservice
{
    Q_OBJECT
public:
    explicit CPyDevoder(QObject *parent = nullptr);
    void parse(const char *data, CPYDATA::mat_trans &PTtopic);
    Eigen::MatrixXd make_mat(CPYDATA::mat_trans &PTtopic);
    void getmat(QByteArray data) override;
    void Bind_Slot(QObject *reciever,const char *method) override;
    void sendMAT(Eigen::MatrixXd mat,Tcpcommunicateservice * usingservice) override;
    void sendMAT(Eigen::MatrixXd &mat,TCPserverservice * usingservice) override;
    void execute( CPYDATA::mat_trans ptopic, QByteArray &sending_data);
    void Server_mode_connect(int portnum) override;
    void sendMAT(Eigen::MatrixXd &mat) override;
    void Client_mode_connect(QString IP,int portnum) override;
    CPYcoderservice* cloneservice() override;
    Tcpcommunicateservice *m_clientservice;
    TCPserverservice *m_serverservice;
    Eigen::MatrixXd returnmat;
    int sendingmode;
    char m_preassigned_mat[4000];//最大允许值,也就是一次最多传输五百个左右元素
signals:
    void matrecieved(Eigen::MatrixXd mat);
public slots:
    void datarecieved(QByteArray data);
};

#endif // CPYDEVODER_H
