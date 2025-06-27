#ifndef _QQQ_AUDI_H
#define _QQQ_AUDI_H

#include <iostream>
#include "Car.h"

class Audi : public Car
{
public:
    virtual ~Audi() {}
    void drive() override
    {
        std::cout << "Driving Audi" << std::endl;
    }
};



#endif //_QQQ_AUDI_H
