#ifndef VALUEOPERATORS_H
#define VALUEOPERATORS_H

#include <Eigen/Dense>

inline double ValueOperator(Eigen::MatrixXd value);
//在此处添加其它类型输入的operator，这样可以比较方便的
//实现不同类型的argmin函数
//例子：
//inline double ValueOperator(std::string value);
//这里的设计模式，如果需要在ValueOperator里面引用
//一些其它的变量，可以通过一个global变量指针，指向一个其它函数的内部变量
//这样就可以实现连续的变量调用了

#endif // VALUEOPERATORS_H
