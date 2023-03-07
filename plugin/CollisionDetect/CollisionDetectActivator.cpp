#include "CollisionDetectActivator.h"


CollisionDetectActivator* CollisionDetectActivator::m_instance=Q_NULLPTR;
PluginContext* CollisionDetectActivator::m_CONTEXT=Q_NULLPTR;
CollisionDetectActivator::CollisionDetectActivator(QObject *parent) : QObject(parent),m_detect(NULL)
{
    m_instance=this;
}
void CollisionDetectActivator::init(PluginContext *CONTEXT)
{
    m_CONTEXT=CONTEXT;
}
void CollisionDetectActivator::start()
{
    m_detect=new collisionCalculator;
}
void CollisionDetectActivator::stop()
{
delete this;

}
