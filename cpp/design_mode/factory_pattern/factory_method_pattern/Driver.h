#ifndef _QQQ_DRIVER_H
#define _QQQ_DRIVER_H

#include "Car.h"
#include "Benz.h"
#include "Bmw.h"
#include "Audi.h"
#include <string>
#include <memory>

class Driver
{
public:
    virtual ~Driver() {};
    virtual std::shared_ptr<Car> driverCar() = 0;
};

#endif //_QQQ_DRIVER_H
