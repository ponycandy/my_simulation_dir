
#include "decoder_manager.h"
#include "C_Python_decodeActivator.h"
#include "defines/CpyDefines.h"
#include "OSGIEVENT.h"

decoder_manager::decoder_manager(QObject *parent)
    : QObject{parent}
{
    m_decode=new CPyDevoder;
    C_Python_decodeActivator::subscribeslot(m_decode,SLOT(datarecieved(QByteArray))
                                            ,OSGIEVENT::TCPHEXRECIEVED,Qt::QueuedConnection);
    qRegisterMetaType<Eigen::MatrixXd>("Eigen::MatrixXd");
    C_Python_decodeActivator::publishsignal(m_decode,SIGNAL(matrecieved(Eigen::MatrixXd))
                                            ,OSGIEVENT::MAT_GET_NOW,Qt::QueuedConnection);
    C_Python_decodeActivator::registerservice(m_decode,"CPYcoderservice");

}

