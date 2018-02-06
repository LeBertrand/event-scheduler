#include "Component.h"

Component::Component()
{
    //ctor
}

Component::~Component()
{
    //dtor
}

Component& Component::operator=(const Component& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
