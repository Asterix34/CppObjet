#include "Container.h"

Container::Container(int size) : size(size)
{
    //ctor
}

Container::~Container()
{
    inventory.clearAndDelete();
}

bool Container::add(Unit *unit) {
    if ( size > 0 && inventory.size() >= size ) {
        // inventory false
        return false;
    }
    inventory.push(unit);
    return true;
}

void Container::remove(Unit *unit) {
    inventory.remove(unit);
}
