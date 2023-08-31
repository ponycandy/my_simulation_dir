#ifndef GREYTHEORY_H
#define GREYTHEORY_H

#include "vector"
#include "Eigen/Dense"


class GreyTheory
{
public:
    GreyTheory();
    void setPrecisionLevel(double c);
    void flushsignledata(double data);
    double rolloutdata(double data);
    void setqueuedmode(int flag,int Nstep);
    void InputData(std::vector<double> data);
    double predict();
    double feedInnewdata(double data);
    std::vector<double> data_series;
    double level;
    int Nsteps;
    int workingMode=0;
private:
};

#endif // GREYTHEORY_H
