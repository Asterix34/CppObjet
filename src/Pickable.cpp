#include "Pickable.h"

Pickable::Pickable()
{
    //ctor
}

Pickable::~Pickable()
{
    //dtor
}

// owner is the "item" owning the interface Pickable, wearer is the picker
bool Pickable::pick(Unit *owner, Unit *wearer) {
    if ( wearer->container && wearer->container->add(owner) ) {
        engine.units.remove(owner);
        return true;
    }
    return false;
}

// will be overriden without masking, we only
// handle the item deletion here (single use item only)
bool Pickable::use(Unit *owner, Unit *wearer) {
    if ( wearer->container ) {
        wearer->container->remove(owner);
        delete owner;
        return true;
    }
    return false;
}

/* healer */
Healer::Healer(float amount) : amount(amount)
{
    //ctor
}

Healer::~Healer()
{
    //dtor
}

bool Healer::use(Unit *owner, Unit *wearer) {
    if ( wearer->destructible ) {
        float amountHealed = wearer->destructible->heal(amount);
        if ( amountHealed > 0 ) {
            // this will only works if the wearer is not full health
            return Pickable::use(owner, wearer);
        }
    }
    return false;
}
