#ifndef MATRIX_SPARSER_H
#define MATRIX_SPARSER_H
#include "MATRIX_SPARSER_global.h"
#include "Eigen/Sparse"
#include "Eigen/Core"
class MATRIX_SPARSER_EXPORT Matrix_sparser
{
public:
	Matrix_sparser();
    void fillin(int i,int j, double value);
    void clearall();
    Eigen::SparseMatrix<double> stack_vertical_blok(Eigen::SparseMatrix<double> mat_upper,Eigen::SparseMatrix<double> mat_low);
    void add_mat_block_vertical(Eigen::MatrixXd mat);
    void add_mat_block(Eigen::MatrixXd mat,int start_x,int start_y);

    void setsize(int width,int height);
    Eigen::SparseMatrix<double> get_sparse_mat();
    std::vector<Eigen::Triplet<double>> tripletList;
    int m_rows;
    int m_cols;
    int cursor_x;
    int cursor_y;
private:
};


#endif // MATRIX_SPARSER_H
