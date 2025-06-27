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
    static std::shared_ptr<Car> driverCar(const std::string& car_name)
    {
        if (!car_name.compare("Benz"))
            return std::make_shared<Benz>();
        else if (!car_name.compare("Bmw"))
            return std::make_shared<Bmw>();
        else if (!car_name.compare("Audi"))
            return std::make_shared<Audi>();

        return nullptr;
    }
};

#endif //_QQQ_DRIVER_H
