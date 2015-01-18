#include "Attacker.h"

Attacker::Attacker(float power) : m_power(power)
{
    //ctor
}

Attacker::~Attacker()
{
    //dtor
}

void Attacker::attack(Unit *owner, Unit *target) {
    // check if target is ok
    if ( target->destructible && !target->destructible->isDead() ) {
        // looks like a double check here, maybe we need another method in destructibe
        if ( m_power - target->destructible->m_defense > 0 ) {
            printf("%s attacks %s for %g hit points.\n",
                   owner->m_name, target->m_name,
                   m_power - target->destructible->m_defense);
        } else {
            printf("%s attacks %s but it has no effect!\n",
                   owner->m_name, target->m_name);
        }
        target->destructible->takeDamage(target, m_power);
    } else {
        printf("%s attacks %s in vain.\n",
               owner->m_name, target->m_name);
    }
}
