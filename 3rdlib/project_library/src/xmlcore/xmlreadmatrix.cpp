#include "xmlcore.h"

bool xmlCore::xmlRead(std::string cName,Eigen::MatrixXd& matrix)
{
    QString matrix_qString = xmlRead(cName);

    if(matrix_qString == "")
    {
        return false;
    }

    QVector<double> matrix_vector;

    int size = matrix_qString.size();

    QString value;
    QString value_reverse;

    int row = 0;

    int col = 0;

    int i = 2;
    QString part;
    while (i < size)
    {
        part=matrix_qString[i];

        while (part != "\t")
        {
            value.clear();
            value_reverse.clear();

            while (part != " " && part != "\n")
            {
                value_reverse.insert(0,part);

                i += 1;
                part=matrix_qString[i];
            }
            col += 1;

            for(int j = 0; j < value_reverse.size(); j++)
            {
                value.insert(0,value_reverse[j]);
            }

            matrix_vector.insert(matrix_vector.begin(),value.toDouble());

            i += 1;
        }
        row +=1;

        i += 1;
    }

    col = col/row;

    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            matrix(i,j) = matrix_vector[matrix_vector.size() - 1 - i*col - j];
        }
    }

    return true;
}
