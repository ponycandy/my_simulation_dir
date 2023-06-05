#include "middleclass.h"

middleclass::middleclass()
{

}

void middleclass::initialize(int num)
{
    m_varaible=new testVaiable(2);
    m_cons = new testCons(1);
    m_cost = new test_cost;
    m_cons->counts();
    m_varaible->do_sthing();
}

