#include "xmlcore.h"

QString xmlCore::
    xmlRead(std::string cName)
{
    QString qName = QString(QString::fromLocal8Bit(cName.c_str()));

    QString value_qString;

    if(!doc_load())
    {
        return "";
    }

    QDomElement root = m_document->documentElement();
    QDomNode node = root.firstChild();
    QDomElement param;
    bool breakFlag = false;
    while(!node.isNull())
    {
        if(node.nodeName() == qName)
        {
            param = node.toElement();

            QDomNodeList list = param.childNodes();

            for(int i = 0; i < list.count(); i++)
            {
                QDomNode n = list.at(i);

                if(n.nodeName() == "value")
                {
                    value_qString = n.toElement().text();

                    breakFlag = true;

                    break;
                }
            }

            if(breakFlag)
            {
                break;
            }
        }

        node = node.nextSibling();
    }

    if(breakFlag)
    {
        return value_qString;
    }
    else
    {
        qDebug()<<"read:找不到参数:"<<qName<<"的值";

        return "";
    }
}

bool xmlCore::xmlRead(std::string cName, int& value)
{
    QString value_qString = xmlRead(cName);

    if(value_qString == "")
    {
        return false;
    }

    value =value_qString.toInt();

    return true;
}

bool xmlCore::xmlRead(std::string cName, double& value)
{
    QString value_qString = xmlRead(cName);

    if(value_qString == "")
    {
        return false;
    }

    value =value_qString.toDouble();

    return true;
}

bool xmlCore::xmlRead(std::string cName, std::string& value)
{
    QString value_qString = xmlRead(cName);

    if(value_qString == "")
    {
        return false;
    }

    value =value_qString.toStdString();

    return true;
}


QMap<QString,QString> xmlCore::xmlReadAllelement()
{
    QMap<QString,QString> mapper;
    if (!m_file->open(QIODevice::ReadOnly))
        qDebug()<<"cant open xml file";
    if (!m_document->setContent(m_file)) {
        m_file->close();
        qDebug()<<"cant open xml file";
    }
    m_file->close();

    // print out the element names of all elements that are direct children
    // of the outermost element.
    QDomElement docElem = m_document->documentElement();

    QDomNode n = docElem.firstChild();
    while(!n.isNull()) {
        QDomElement e = n.toElement(); // try to convert the node to an element.
        if(!e.isNull()) {
            qDebug()<< qPrintable(e.tagName()) << '\n'; // the node really is an element.
            QDomNodeList list = e.childNodes();
            QString value_qString;
            for(int i = 0; i < list.count(); i++)
            {
                QDomNode n = list.at(i);

                if(n.nodeName() == "value")
                {
                    value_qString = n.toElement().text();

                    break;
                }
            }
            mapper.insert(e.tagName(),value_qString);
            qDebug()<<value_qString;
        }
        n = n.nextSibling();
    }
}

