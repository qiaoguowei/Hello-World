#include "Abstraction.h"
#include "AbstractionImp.h"
#include <iostream>

int main(int argc, char *argv[])
{
    AbstractionImp* imp = new ConcreteAbstractionImpA();
    Abstraction* abs = new RefinedAbstraction(imp);
    abs->operation();

    delete abs;
    abs = nullptr;
    delete imp;
    imp = nullptr;

    return 0;
}
