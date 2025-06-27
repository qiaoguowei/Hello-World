#include "Car.h"
#include "Benz.h"
#include "Bmw.h"
#include "Audi.h"
#include "Driver.h"
#include <iostream>
#include <memory>

int main()
{
    std::shared_ptr<Car> car = Driver::driverCar("Benz");
    if (!car)
    {
        std::cout << "You're driving the wrong car." << std::endl;
        return -1;
    }

    car->drive();
}
