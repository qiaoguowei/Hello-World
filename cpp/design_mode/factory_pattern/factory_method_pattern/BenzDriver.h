#ifndef _QQQ_BENZ_DRIVER_H
#define _QQQ_BENZ_DRIVER_H

#include <memory>
#include "Car.h"
#include "Benz.h"
#include "Driver.h"

class BenzDriver : public Driver
{
public:
    ~BenzDriver() override
    {
    }

    std::shared_ptr<Car> driverCar() override
    {
        return std::make_shared<Benz>();
    }
};

#endif //_QQQ_BENZ_DRIVER_H
