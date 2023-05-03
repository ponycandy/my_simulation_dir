#include "Matrix_sparser.h"
Matrix_sparser::Matrix_sparser()
{
    cursor_x=0;
    cursor_y=0;
}

void Matrix_sparser::fillin(int i, int j, double value)
{
    tripletList.push_back(Eigen::Triplet<double>(i,j,value));
}

void Matrix_sparser::clearall()
{
    tripletList.clear();
}

Eigen::SparseMatrix<double> Matrix_sparser::stack_vertical_blok(Eigen::SparseMatrix<double> mat_upper, Eigen::SparseMatrix<double> mat_low)
{
    clearall();
    m_rows=mat_upper.rows()+mat_low.rows();
    m_cols=mat_upper.cols();
    int upper_rows=mat_upper.rows();
    int lower_rows=mat_low.rows();

    Eigen::SparseMatrix<double> mat(m_rows,m_cols);
    for (int k=0; k<mat_upper.outerSize(); ++k)
    {
        for (Eigen::SparseMatrix<double>::InnerIterator it(mat_upper,k); it; ++it)
        {
            upper_rows=it.row();lower_rows=it.col();
            fillin(it.row(),it.col(),it.value());//不确定这里要不要减1
        }
    }
    for (int k=0; k<mat_low.outerSize(); ++k)
    {
        for (Eigen::SparseMatrix<double>::InnerIterator it(mat_low,k); it; ++it)
        {
            upper_rows=it.row();lower_rows=it.col();

            fillin(it.row()  + mat_upper.rows(),it.col(),it.value());//不确定这里要不要减1
        }
    }

    return get_sparse_mat();

}

void Matrix_sparser::add_mat_block_vertical(Eigen::MatrixXd mat)
{
    //连续进行垂直堆叠的时候使用
    for(int i=0;i<mat.rows();i++)
    {
        for(int j=0;j<mat.cols();j++)
        {
            tripletList.push_back(
                Eigen::Triplet<double>(cursor_x+i,j,mat(i,j)));
        }
    }
    cursor_x+=mat.rows();
}


void Matrix_sparser::add_mat_block(Eigen::MatrixXd mat, int start_x, int start_y)
{
    for(int i=0;i<mat.rows();i++)
    {
        for(int j=0;j<mat.cols();j++)
        {
            tripletList.push_back(
                Eigen::Triplet<double>(start_x+i,start_y+j,mat(i,j)));
        }
    }
}

Eigen::SparseMatrix<double> Matrix_sparser::make_dense_sparse(Eigen::MatrixXd mat)
{
    clearall();
    setsize(mat.cols(),mat.rows());
    for(int i=0;i<mat.rows();i++)
    {
        for(int j=0;j<mat.cols();j++)
        {
            if(mat(i,j) !=0)
            {
                tripletList.push_back(
                    Eigen::Triplet<double>(i,j,mat(i,j)));
            }
        }
    }
    return get_sparse_mat();
}

void Matrix_sparser::setsize(int width, int height)
{
    m_rows=height;
    m_cols=width;
}

Eigen::SparseMatrix<double> Matrix_sparser::get_sparse_mat()
{
    Eigen::SparseMatrix<double> spmat;
    spmat.resize(m_rows,m_cols);
    spmat.setFromTriplets(tripletList.begin(), tripletList.end());
    return spmat;
}
