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

    int row = matrix.rows();

    int col = matrix.cols();

    matrix_qString.replace("\t"," ");
    matrix_qString.replace("\r"," ");
    matrix_qString.replace("\n"," ");
    QStringList list = matrix_qString.split(" ", QString::SkipEmptyParts);
    int i=0;
    int entry1=0;
    int entry2=0;
    for (const QString &word : list)
    {
        entry1=i / col;
        entry2=i % col;
        matrix(entry1, entry2) = word.toDouble();
        i++;
    }
    return true;
}
