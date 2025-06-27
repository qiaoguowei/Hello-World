#ifndef _QQQ_BENZ_H
#define _QQQ_BENZ_H

#include <iostream>
#include "Car.h"

class Benz : public Car
{
public:
    virtual ~Benz() {}
    void drive() override
    {
        std::cout << "Driving Benz" << std::endl;
    }
};


#endif //_QQQ_BENZ_H
