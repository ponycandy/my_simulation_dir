#ifndef COLLISIONRESULT_H
#define COLLISIONRESULT_H


class collison_result
{
public:


    virtual ~DrawOperation(){}
    virtual void draw() = 0;
    Animateservice *m_animator;
};

#endif 

