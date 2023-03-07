#include "trtmanager.h"

trtmanager::trtmanager(QObject *parent) : QObject(parent),m_ui(NULL)
{
    m_ui=new trtUI;
    m_ui->show();
}
