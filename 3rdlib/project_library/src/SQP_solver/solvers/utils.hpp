#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <Eigen/Dense>
#include <Eigen/Eigenvalues>

template <typename qp_t>
void print_qp(qp_t qp)
{
    Eigen::IOFormat fmt(Eigen::StreamPrecision, 0, ", ", ",", "[", "]", "[", "]");
    std::cout << "P = " << qp.P.format(fmt) << '\n';
    std::cout << "q = " << qp.q.transpose().format(fmt) << '\n';
    std::cout << "A = " << qp.A.format(fmt) << '\n';
    std::cout << "l = " << qp.l.transpose().format(fmt) << '\n';
    std::cout << "u = " << qp.u.transpose().format(fmt) << '\n';
}

template <typename Mat>
bool is_psd(Mat &h)
{
    Eigen::EigenSolver<Mat> eigensolver(h);
    for (int i = 0; i < eigensolver.eigenvalues().RowsAtCompileTime; i++) {
        double v = eigensolver.eigenvalues()(i).real();
        if (v <= 0) {
            return false;
        }
    }
    return true;
}

#endif /* UTILS_HPP */