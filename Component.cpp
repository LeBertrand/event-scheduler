#include "Component.h"
#include "LinkedListQueue.cpp"

Component::Component()
{
    qu = new LinkedListQueue();
}

Component::~Component()
{
    delete qu;
}

Component& Component::operator=(const Component& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

void Component::pushJob(int serial)
{
    qu->append(serial);
    idle = false;
}
