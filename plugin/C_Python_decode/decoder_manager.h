
#ifndef DECODER_MANAGER_H
#define DECODER_MANAGER_H


#include <QObject>

#include <cpydevoder.h>
class decoder_manager : public QObject
{
    Q_OBJECT
public:
    explicit decoder_manager(QObject *parent = nullptr);
    CPyDevoder *m_decode;

signals:

};

#endif // DECODER_MANAGER_H
