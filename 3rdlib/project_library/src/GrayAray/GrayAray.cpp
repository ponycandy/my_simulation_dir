#include "grayaray.h"
#include "iostream"
GrayAray::GrayAray()
{
    cahceElement=0;
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
    //这里要考虑元素数目不够的情况
    if(cahceElement<3)
    {
        std::cout<<"predictOnce needs at least 3 element to make prediction";
        return;
    }
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=group_vec[i];
        returnstates(i,0)=a_array->predict();
    }
}

void GrayAray::GetCurrentValue(Eigen::MatrixXd &returnstates)
{
    GreyTheory *a_array=group_vec[0];
    a_array->Nsteps=a_array->data_series.size();
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

void GrayAray::setMaxqueue(int size,int statenums)
{
    statenum=statenums;
    maxqueue=size;
    group_vec.clear();
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=new GreyTheory;
        group_vec.push_back(a_array);
    }
}

void GrayAray::GetReturnQue(Eigen::MatrixXd &returnstates, Eigen::MatrixXd &input)
{
    if(cahceElement>=maxqueue)
    {
        GetreturnState(returnstates, input);
        return;
    }
    else
    {
        if(cahceElement<=1)
        {
            returnstates=input.eval();//只有两个数据是无法预测的，起码有两个以上数据
            QueuInsert(input);
        }
        else
        {
            QueuInsert(input);
            predictOnce(returnstates);
        }
        return;


    }

}

void GrayAray::QueuInsert(Eigen::MatrixXd &input)
{
    if(cahceElement<maxqueue)
    {
        for(int i=0;i<statenum;i++)
        {
            GreyTheory *a_array=group_vec[i];
            a_array->data_series.push_back(input(i,0));

        }
        cahceElement++;
        return;
    }
    else
    {
        for(int i=0;i<statenum;i++)
        {
            GreyTheory *a_array=group_vec[i];

            a_array->flushsignledata(input(i,0));

        }
        return;
    }

}

void GrayAray::IteratePredict(Eigen::MatrixXd &returnstates)
{

    if(cahceElement==0)
    {
        std::cout<<"at least 1 element is required!";
        return;
    }
    if(cahceElement>=maxqueue)
    {
        for(int i=0;i<statenum;i++)
        {
            GreyTheory *a_array=group_vec[i];
            returnstates(i,0)=a_array->predictSingle();

        }
        return;
    }
    else
    {
        if(cahceElement==1)
        {
            for(int i=0;i<statenum;i++)
            {
                GreyTheory *a_array=group_vec[i];
                returnstates(i,0)=a_array->data_series[0];//返回最后一个插入值

            }
            return;
        }
        else
        {
            for(int i=0;i<statenum;i++)
            {
                GreyTheory *a_array=group_vec[i];
                returnstates(i,0)=a_array->predictSingle();

            }
            return;
        }


    }

}

void GrayAray::clearsteps()
{
    for(int i=0;i<statenum;i++)
    {
        GreyTheory *a_array=group_vec[i];
        a_array->ResetSteps();

    }
}

