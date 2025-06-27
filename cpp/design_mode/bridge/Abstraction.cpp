#include "Abstraction.h"
#include "AbstractionImp.h"
#include <iostream>

Abstraction::Abstraction()
{
}

Abstraction::~Abstraction()
{
}

RefinedAbstraction::RefinedAbstraction(AbstractionImp *imp)
    : _imp(imp)
{
}

RefinedAbstraction::~RefinedAbstraction()
{
}

void RefinedAbstraction::operation()
{
    _imp->operation();
}
