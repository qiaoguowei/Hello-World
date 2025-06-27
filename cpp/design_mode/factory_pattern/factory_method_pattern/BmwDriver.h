#ifndef _QQQ_BMW_DRIVER_H
#define _QQQ_BMW_DRIVER_H

#include <memory>
#include "Car.h"
#include "Bmw.h"
#include "Driver.h"

class BmwDriver : public Driver
{
public:
    ~BmwDriver() override
    {
    }

    std::shared_ptr<Car> driverCar() override
    {
        return std::make_shared<Bmw>();
    }
};

#endif //_QQQ_BMW_DRIVER_H
