#include "AbstractionImp.h"
#include <iostream>

AbstractionImp::AbstractionImp()
{
}

AbstractionImp::~AbstractionImp()
{
}

ConcreteAbstractionImpA::ConcreteAbstractionImpA()
{
}

ConcreteAbstractionImpA::~ConcreteAbstractionImpA()
{
}

void ConcreteAbstractionImpA::operation()
{
    std::cout << "ConcreteAbstractionImpA......" << std::endl;
}

ConcreteAbstractionImpB::ConcreteAbstractionImpB()
{
}

ConcreteAbstractionImpB::~ConcreteAbstractionImpB()
{
}

void ConcreteAbstractionImpB::operation()
{
    std::cout << "ConcreteAbstractionImpB......" << std::endl;
}



