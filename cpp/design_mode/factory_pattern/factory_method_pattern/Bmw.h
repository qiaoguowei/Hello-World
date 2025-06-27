#ifndef _QQQ_BMW_H
#define _QQQ_BMW_H

#include <iostream>
#include "Car.h"

class Bmw : public Car
{
public:
    virtual ~Bmw() {}
    void drive() override
    {
        std::cout << "Driving Bmw" << std::endl;
    }
};


#endif //_QQQ_BMW_H
