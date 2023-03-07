#ifndef CLASSA_TEST_H
#define CLASSA_TEST_H
#include "CLASSA_TEST_global.h"

class CLASSA_TEST_EXPORT classA_test
{
public:
    void dosomething();
    void setID(int num);
    int getID();
private:
    int ID;
};


#endif // CLASSA_TEST_H
