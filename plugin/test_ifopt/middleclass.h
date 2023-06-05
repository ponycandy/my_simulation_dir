#ifndef MIDDLECLASS_H
#define MIDDLECLASS_H
#include "testvaiable.h"
#include "testcons.h"
#include "test_cost.h"
class middleclass
{
public:
    middleclass();
    testVaiable *m_varaible;
    testCons *m_cons;
    test_cost *m_cost;
    void initialize(int num);
};

#endif // MIDDLECLASS_H
