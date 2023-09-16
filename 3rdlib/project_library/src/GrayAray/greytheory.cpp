#include "GreyTheory.h"

GreyTheory::GreyTheory()
{
    level=0.35;
    Nsteps=10;//默认数据缓存量
    data_series.clear();
    cache_A=0;
    cache_B=0;
}

void GreyTheory::setPrecisionLevel(double c)
{
    level=c;
}

void GreyTheory::flushsignledata(double data)
{
    int size=data_series.size();
    for(int i=0;i<size-1;i++)
    {
        data_series[i]=data_series[i+1];
    }
    data_series[size-1]=data;
}

double GreyTheory::predictSingle()
{
    //必须首先使用predictOnce然后再Iterate
    if(cache_A==0)
    {
        Cachsteps++;
        return data_series[data_series.size()-1];//说明是直线或者其它理由没拟合，返回最后一个

    }
    double value=(data_series[0]-cache_B/cache_A)*(1-exp(cache_A))*exp(-cache_A*(Cachsteps+1));
    Cachsteps++;
    return value;
}

void GreyTheory::ResetSteps()
{
    int size=data_series.size();
    Cachsteps=size-1;
}

double GreyTheory::rolloutdata(double data)
{
    int size=data_series.size();
    Cachsteps=size-1;
    flushsignledata(data);
    return predict();
}

void GreyTheory::setqueuedmode(int flag, int Nstep)
{
    workingMode=flag;
}

void GreyTheory::InputData(std::vector<double> data)
{
    data_series=data;
    Nsteps=data.size();
}

double GreyTheory::predict()
{


    int size=data_series.size();
    Cachsteps=size-1;
    std::vector<double> Y_series;
    std::vector<double> Z_series;
    double xiter=0;
    double mean=0;
    for(int i=0;i<size;i++)
    {
        xiter+=data_series[i];
        Y_series.push_back(xiter);
    }
    mean=xiter/size;
    Eigen::MatrixXd Bmat;
    Bmat.resize(size-1,2);
    Bmat.setZero();//注意B的Rank小于2的情况，虽然不太可能，但是这会导致最小二乘失败
    Eigen::MatrixXd sai;
    sai.resize(size-1,1);
    sai.setZero();
    //失败后，则不求逆,这说明下一个最可能的值，和历史值一样
    for(int i=0;i<size-1;i++)//尺寸小1
    {
        double value=0.5*(Y_series[i]+Y_series[i+1]);
        Z_series.push_back(value);
        Bmat(i,0)=-value;Bmat(i,1)=1;
        sai(i,0)=data_series[i+1];
    }
    Eigen::MatrixXd BmatT=Bmat.transpose();
    Eigen::MatrixXd BmatDet=BmatT*Bmat;
    double value=BmatDet.determinant();
    if(value==0)
    {
        return data_series[size-1];
    }
    Eigen::MatrixXd u_value=BmatDet.inverse()*BmatT*sai;
    double a=u_value(0,0);
    cache_A=a;
    //这里需要做一下修正，a太过于近于0会出问题，而且有的时候，矩阵秩检测查不到这个问题
    //这就是矩阵的秩约等于0的情况，bug居然在这里呢....
    if(abs(a)<1e-7)
    {
        cache_A=0;
        return data_series[size-1];
    }
    double b=u_value(1,0);
    cache_B=b;
    std::vector<double> predict_series;


    double sigma_predict=0;
    for(int i=0;i<size;i++)//尺寸小1,计算求和
    {
        double value=(data_series[0]-b/a)*(1-exp(a))*exp(-a*(i+1));
        sigma_predict+=value;
        predict_series.push_back(value);
    }
    //计算第一个方差
    double S_1=0;
    for(int i=0;i<size;i++)//尺寸小1,计算求和
    {
        S_1+=pow(data_series[i]-mean,2);
    }
    S_1/=size;

    double S_2=0;
    for(int i=2;i<=size;i++)//尺寸小1,计算求和
    {
        S_2+=(data_series[i-1]-predict_series[i-2]);
        //请看公式，这里是不一样的
    }
    S_2/=(size-1);
    mean=S_2;


    S_2=0;
    for(int i=2;i<=size;i++)//尺寸小1,计算求和
    {
        S_2+=pow(data_series[i-1]-predict_series[i-2]-mean,2);
        //请看公式，这里是不一样的
    }
    S_2/=(size-1);

    double c=S_2/S_1;
    if(level>c)
    {
        return predict_series[size-1];
    }
    else
    {
        return data_series[size-1];
    }

}
