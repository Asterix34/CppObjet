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
        engine.gui->message(TCODColor::lightGrey, "You pick the %s.", owner->m_name);
        engine.gameStatus=Engine::NEW_TURN; // will let a turn pass for each item

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

/* LightningBolt */
LightningBolt::LightningBolt(float range, float damage)
    : range(range), damage(damage) {

}

bool LightningBolt::use(Unit *owner, Unit *wearer) {
    Unit *closestMonster = engine.getClosestMonster(wearer->m_x, wearer->m_y, range);
    if ( ! closestMonster ) {
        engine.gui->message(TCODColor::lightGrey, "No enemy is close enough to strike.");
        return false;
    }
    float realDamage = closestMonster->destructible->takeDamage(closestMonster, damage);
    engine.gui->message(TCODColor::lightBlue,
        "A lightning bolt strike the %s with a loud thunder!\n"
        "The damage is %g hit points.",
        closestMonster->m_name, realDamage);

    return Pickable::use(owner, wearer);
}

/* Fireball */
Fireball::Fireball(float range, float damage)
    : LightningBolt(range, damage) {

}

bool Fireball::use(Unit *owner, Unit *wearer) {
    engine.gui->message(TCODColor::cyan,
        "Left-click a target tile to cast a fireball\nRight click to cancel...");

    int x, y;
    if (! engine.pickATile(&x, &y)) { // this will launch another window to select a tile
        return false;
    }
    // burn everything in range, including player
    engine.gui->message(TCODColor::orange,
        "The fireball explodes, burning everything within %g tiles!", range);

    // the usual unit loop, i need to find a way to refactor that
    for (Unit **iterator=engine.units.begin();
            iterator != engine.units.end(); iterator++) {
        Unit *unit=*iterator;
        if ( unit->destructible && !unit->destructible->isDead()
                && unit->getDistance(x, y) <= range ) {
            // message conception fail, either the number of dmg is wrong,
            // either my cavader gets dmg, i need a method to return mitigated dmg
            engine.gui->message(TCODColor::orange,
                "The %s gets burnt for %g hit points.", unit->m_name, damage);
            unit->destructible->takeDamage(unit, damage);
            // this will destroy the scroll
            return Pickable::use(owner, wearer);
        }
    }
    return false;
}

