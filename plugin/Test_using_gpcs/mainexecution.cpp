#include "mainexecution.h"

mainExecution::mainExecution(QObject *parent)
    : QObject{parent}
{
    nh=new gpcs::gpcsnode;


    nh->init("Qt_Node");//连接到kernel
  //  somepuber = nh->advertise("Test_Pub_Topic");//注册发布者
    nh->subscribe("Test_Mat_Topic", std::bind(&mainExecution::gpcscallback_2, this,std::placeholders::_1));

  //  nh->subscribe("Test_Sub_Topic", std::bind(&mainExecution::gpcscallback, this,std::placeholders::_1));
  //  m_timer = new QTimer(this);
   // connect(m_timer, SIGNAL(timeout()), this, SLOT(send_messages()));
   // m_timer->start(100);

    m_timer1 = new QTimer(this);
    connect(m_timer1, SIGNAL(timeout()), this, SLOT(spinonce()));
    m_timer1->start(30);
}

void mainExecution::gpcscallback(const std::string &data)
{
    MyData recievedData = gpcs::struct_load<MyData>(data);
    std::cout << "reply data: id:" << recievedData.id << "  value:" << recievedData.value
              << "    name:" << recievedData.name << std::endl;
}

void mainExecution::gpcscallback_2(const std::string &data)
{
    std::cout<<"start this catch"<<std::endl;

    gpcs::mat matrix=gpcs::struct_load<gpcs::mat>(data);
    matrix[0][0]=-10;
    for(int i=0;i<matrix.rows;i++)
    {
        for(int j=0;j<matrix.cols;j++)
        {
            std::cout<<"matrix on rows "<<i<<" cols "<<j<<" is "<<matrix[i][j]<<std::endl;
        }
    }
    std::cout<<"end this catch"<<std::endl;
}

void mainExecution::send_messages()
{
    MyData testData;
    testData.id = 10;
    testData.value = 1.8;
    std::string message = "from Qt_Node!";
    std::strcpy(testData.name, message.c_str());
    somepuber->publish(testData);
}

void mainExecution::spinonce()
{
    nh->spinonce();
}
