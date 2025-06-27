#ifndef _QQQ_AUDI_DRIVER_H
#define _QQQ_AUDI_DRIVER_H

#include <memory>
#include "Driver.h"
#include "Car.h"
#include "Audi.h"

class AudiDriver : public Driver
{
public:
    ~AudiDriver() override
    {
    }

    std::shared_ptr<Car> driverCar() override
    {
        return std::make_shared<Audi>();
    }
};

#endif //_QQQ_AUDI_DRIVER_H
