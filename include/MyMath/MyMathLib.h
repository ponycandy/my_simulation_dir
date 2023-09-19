#ifndef ESSENTIALHEAD_H
#define ESSENTIALHEAD_H

#include <iostream>
#include <vector>

#include "ValueOperators.h"
const double mathpi = 3.141592653589793;
inline int findSmallestIndex(const std::vector<double> &vec)
{
    if (vec.empty()) {
        std::cerr << "Error: Empty vector." << std::endl;
        return -1;  // Return -1 to indicate an error or handle it differently
    }

    double smallest = vec[0];
    int smallestIndex = 0;

    for (int i = 1; i < vec.size(); ++i) {
        if (vec[i] < smallest) {
            smallest = vec[i];
            smallestIndex = i;
        }
    }

    return smallestIndex;
}

inline double normalize(double angle)
{
    double remainder = fmod(angle, 2 * mathpi);
    if(isnan(remainder))
    {
        int a=1;
    }
    if (remainder > 0 && remainder > mathpi) {
        remainder -= 2 * mathpi;
    }
    if (remainder < 0 && remainder < -mathpi) {
        remainder += 2 * mathpi;
    }
    return remainder;
}

inline double get_angle(double x, double y)
{
    double angle = std::atan2(y, x);

    return normalize(angle);
}

inline double calculateAngleBetweenVectors(const Eigen::MatrixXd &v1, const Eigen::MatrixXd &v2)
{
    // Calculate the dot product
    double dotProduct = (v1.transpose() *v2)(0,0);

    // Calculate the magnitudes (norms) of the vectors
    double v1Magnitude = v1.norm();
    double v2Magnitude = v2.norm();

    // Calculate the angle in radians
    double angleRadians = std::acos(dotProduct / (v1Magnitude * v2Magnitude));

    // Return the angle in radians
    return normalize(angleRadians);
}

template<typename T>
inline const T* argmin(const std::vector<T>& values, double (*ValueOperator)(T)) {
    if (values.empty())
        return nullptr;

    const T* minElement = &values[0];
    double minValue = ValueOperator(*minElement);

    for (const T& value : values) {
        double calculatedValue = ValueOperator(value);
        if (calculatedValue < minValue) {
            minValue = calculatedValue;
            minElement = &value;
        }
    }

    return minElement;
}

inline bool Point_on_line(Eigen::MatrixXd &startp,Eigen::MatrixXd &endp,Eigen::MatrixXd &TargetPoint)
{
    if(startp==TargetPoint || endp==TargetPoint)
    {
        return true;
    }
    Eigen::MatrixXd vector_1=TargetPoint-startp;
    Eigen::MatrixXd vector_2=endp-TargetPoint;
    vector_2=vector_1.normalized()-vector_2.normalized();
    if(vector_2.norm()<0.001)
    {
        return true;
    }
    else
    {
        return false;
    }

}
#endif // ESSENTIALHEAD_H
