#include "lvdai.h"

Lvdai::Lvdai(QObject *parent) : QObject(parent)
{

}

FeedBackState Lvdai::StateTransition(const ControlCommand &control, const ManipulateState &statechange, const EnviromentChange &Env)
{
    //暂时不知道按照何种方式反馈，目前暂时认为state=control为控制函数
    //随机因素也暂时不确定
    FeedBackState stateFeedback;

    //do something
    return stateFeedback;
}


