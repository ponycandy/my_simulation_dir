#include "xmlcore.h"

bool xmlCore::xmlWrite(std::string cName, int value)
{
    int a=0;
    bool value_exist=xmlRead(cName,a);
    if(value_exist==false)
    {
        if(!doc_load())
        {
            return false;
        }

        QDomElement root = m_document->documentElement();
        m_document->appendChild(root);

        QString qName = QString(QString::fromLocal8Bit(cName.c_str()));
        paramNameCheck(qName);

        QDomElement param = m_document->createElement(qName);
        param.setAttribute("type","int");

        QDomElement param_velue = m_document->createElement("value");

        QString value_qString = QString::number(value);
        text = m_document->createTextNode(value_qString);

        param_velue.appendChild(text);
        param.appendChild(param_velue);
        root.appendChild(param);

        if(!doc_write())
        {
            return false;
        }

        paramName_vector.insert(paramName_vector.begin() , qName);
    }
    else
    {
        QFile inputFile(fileName);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open input file";
            return false;
        }

        // Create a xml stream reader
        QXmlStreamReader reader(&inputFile);

        // Create a temporary xml file for writing
        QFile outputFile("temp.xml");
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open output file";
            return false;
        }

        // Create a xml stream writer
        QXmlStreamWriter writer(&outputFile);
        writer.setAutoFormatting(true);

        // Copy the xml content from input to output, with modification
        while (!reader.atEnd())
        {
            // Read the next token
            reader.readNext();

            // Write the token to the output file
            writer.writeCurrentToken(reader);

            // Check if it is a start element
            if (reader.isStartElement())
            {
                // Get the name of the element
                QString name = reader.name().toString();

                // Check if it is the somevalue tag
                if (name == QString::fromStdString(cName))
                {
                    // Skip to the next element
                    reader.readNext();
                    QString nameofelement=reader.name().toString();
                    reader.readNext();
                    nameofelement=reader.name().toString();
                    // Check if it is the value tag
                    if (reader.isStartElement() && nameofelement == QString("value"))
                    {
                        // Write the modified value tag with 10 as the text
                        writer.writeStartElement("value");
                        writer.writeCharacters(QString::number(value));
                        reader.readNext();
                    }
                }
            }
        }

        // Check for any errors
        if (reader.hasError())
        {
            qWarning() << "Error reading xml file:" << reader.errorString();
            return false;
        }

        // Close the files
        inputFile.close();
        outputFile.close();

        // Rename the temporary file to the original file name
        QFile::remove(fileName);
        QFile::rename("temp.xml", fileName);
    }

    return true;
}

bool xmlCore::xmlWrite(std::string cName, double value)
{
    double a=0;
    bool value_exist=xmlRead(cName,a);
    if(value_exist==false)
    {
        if(!doc_load())
        {
            return false;
        }

        QDomElement root = m_document->documentElement();
        m_document->appendChild(root);

        QString qName = QString(QString::fromLocal8Bit(cName.c_str()));
        paramNameCheck(qName);

        QDomElement param = m_document->createElement(qName);
        param.setAttribute("type","double");

        QDomElement param_velue = m_document->createElement("value");

        QString value_qString = QString::number(value);
        text = m_document->createTextNode(value_qString);

        param_velue.appendChild(text);
        param.appendChild(param_velue);
        root.appendChild(param);

        if(!doc_write())
        {
            return false;
        }

        paramName_vector.insert(paramName_vector.begin() , qName);
    }
    else
    {
        QFile inputFile(fileName);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open input file";
            return false;
        }

        // Create a xml stream reader
        QXmlStreamReader reader(&inputFile);

        // Create a temporary xml file for writing
        QFile outputFile("temp.xml");
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open output file";
            return false;
        }

        // Create a xml stream writer
        QXmlStreamWriter writer(&outputFile);
        writer.setAutoFormatting(true);

        // Copy the xml content from input to output, with modification
        while (!reader.atEnd())
        {
            // Read the next token
            reader.readNext();

            // Write the token to the output file
            writer.writeCurrentToken(reader);

            // Check if it is a start element
            if (reader.isStartElement())
            {
                // Get the name of the element
                QString name = reader.name().toString();

                // Check if it is the somevalue tag
                if (name == QString::fromStdString(cName))
                {
                    // Skip to the next element
                    reader.readNext();
                    QString nameofelement=reader.name().toString();
                    reader.readNext();
                    nameofelement=reader.name().toString();
                    // Check if it is the value tag
                    if (reader.isStartElement() && nameofelement == QString("value"))
                    {
                        writer.writeStartElement("value");
                        writer.writeCharacters(QString::number(value));
                        reader.readNext();
                    }
                }
            }
        }

        if (reader.hasError())
        {
            qWarning() << "Error reading xml file:" << reader.errorString();
            return false;
        }

        // Close the files
        inputFile.close();
        outputFile.close();

        // Rename the temporary file to the original file name
        QFile::remove(fileName);
        QFile::rename("temp.xml", fileName);
    }

    return true;
}

bool xmlCore::xmlWrite(std::string cName, std::string value)
{
    std::string a=0;
    bool value_exist=xmlRead(cName,a);
    if(value_exist==false)
    {
        if(!doc_load())
        {
            return false;
        }

        QDomElement root = m_document->documentElement();
        m_document->appendChild(root);

        QString qName = QString(QString::fromLocal8Bit(cName.c_str()));
        paramNameCheck(qName);

        QDomElement param = m_document->createElement(qName);
        param.setAttribute("type","string");

        QDomElement param_velue = m_document->createElement("value");

        QString value_qString = QString(QString::fromLocal8Bit(value.c_str()));
        text = m_document->createTextNode(value_qString);

        param_velue.appendChild(text);
        param.appendChild(param_velue);
        root.appendChild(param);

        if(!doc_write())
        {
            return false;
        }

        paramName_vector.insert(paramName_vector.begin() , qName);
    }

    else
    {
        QFile inputFile(fileName);
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open input file";
            return false;
        }

        // Create a xml stream reader
        QXmlStreamReader reader(&inputFile);

        // Create a temporary xml file for writing
        QFile outputFile("temp.xml");
        if (!outputFile.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            qWarning() << "Failed to open output file";
            return false;
        }

        // Create a xml stream writer
        QXmlStreamWriter writer(&outputFile);
        writer.setAutoFormatting(true);

        // Copy the xml content from input to output, with modification
        while (!reader.atEnd())
        {
            // Read the next token
            reader.readNext();

            // Write the token to the output file
            writer.writeCurrentToken(reader);

            // Check if it is a start element
            if (reader.isStartElement())
            {
                // Get the name of the element
                QString name = reader.name().toString();

                // Check if it is the somevalue tag
                if (name == QString::fromStdString(cName))
                {
                    // Skip to the next element
                    reader.readNext();
                    QString nameofelement=reader.name().toString();
                    reader.readNext();
                    nameofelement=reader.name().toString();
                    // Check if it is the value tag
                    if (reader.isStartElement() && nameofelement == QString("value"))
                    {
                        writer.writeStartElement("value");
                        writer.writeCharacters(QString::fromStdString(value));
                        reader.readNext();
                    }
                }
            }
        }

        if (reader.hasError())
        {
            qWarning() << "Error reading xml file:" << reader.errorString();
            return false;
        }

        // Close the files
        inputFile.close();
        outputFile.close();

        // Rename the temporary file to the original file name
        QFile::remove(fileName);
        QFile::rename("temp.xml", fileName);
    }


    return true;
}

bool xmlCore::xmlWrite(std::string cName, Eigen::MatrixXd value)
{
    if(!doc_load())
    {
        return false;
    }

    QDomElement root = m_document->documentElement();
    m_document->appendChild(root);

    QString qName = QString(QString::fromLocal8Bit(cName.c_str()));
    paramNameCheck(qName);

    QDomElement param = m_document->createElement(qName);
    param.setAttribute("type","Eigen::MatrixXd");

    QDomElement param_velue = m_document->createElement("value");

    QString value_qString;

    value_qString.append("\n\t");

    for(int i = 0; i < value.rows(); i++)
    {
        for(int j = 0; j < value.cols(); j++)
        {
            value_qString.append(QString::number(value(i,j)));

            if(j != value.cols() - 1)
            {
                value_qString.append(" ");
            }
            else
            {
                value_qString.append("\n\t");
            }
        }
    }

    text = m_document->createTextNode(value_qString);

    param_velue.appendChild(text);
    param.appendChild(param_velue);
    root.appendChild(param);

    if(!doc_write())
    {
        return false;
    }

    paramName_vector.insert(paramName_vector.begin() , qName);

    return true;
}
