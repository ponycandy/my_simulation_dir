#include "grayaray.h"

GrayAray::GrayAray()
{

}

void GrayAray::resize(int num)
{
    statenum=num;
    group_vec.clear();
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=new GreyTheory;
        group_vec.push_back(a_array);
    }

}

void GrayAray::storeInitial(Eigen::MatrixXd &states)
{
    //形式statenum*Nsteps
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=group_vec[i];
        std::vector<double> temparray;
        for(int j=0;j<states.cols();j++)
        {
            temparray.push_back(states(i,j));
        }
        a_array->InputData(temparray);
    }
}

void GrayAray::GetreturnState(Eigen::MatrixXd &returnstates, Eigen::MatrixXd &input)
{
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=group_vec[i];
        returnstates(i,0)=a_array->rolloutdata(input(i,0));
    }
}
void GrayAray::predictOnce(Eigen::MatrixXd &returnstates)
{
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=group_vec[i];
        returnstates(i,0)=a_array->predict();
    }
}
void GrayAray::GetCurrentValue(Eigen::MatrixXd &returnstates)
{
    GreyTheory *a_array=group_vec[0];
    int size=a_array->Nsteps;
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=group_vec[i];
        for(int j=0;j<size;j++)
        {
            returnstates(i,j)=a_array->data_series[j];
        }

    }
}
