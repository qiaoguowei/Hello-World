#include "BenzDriver.h"

int main()
{
    std::shared_ptr<Driver> driver = std::make_shared<BenzDriver>();
    std::shared_ptr<Car> car = driver->driverCar();
    car->drive();
}
