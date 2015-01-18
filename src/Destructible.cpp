#include "Destructible.h"

Destructible::Destructible(float maxHp, float defense, const char *corpseName) :
    m_maxHp(maxHp), m_hp(maxHp), m_defense(defense), m_corpseName(corpseName)
{
    //ctor
}

MonsterDestructible::MonsterDestructible( float maxHp, float defense, const char *corpseName) :
    Destructible(maxHp, defense, corpseName)
{

}

PlayerDestructible::PlayerDestructible( float maxHp, float defense, const char *corpseName) :
    Destructible(maxHp, defense, corpseName)
{

}


Destructible::~Destructible()
{
    //dtor
}

float Destructible::takeDamage(Unit *owner, float damage) {
    damage -= m_defense; // defense reducts incoming damage
    if (damage > 0) {
        m_hp-= damage;
        if ( isDead() ) {
            die(owner);
        }
    } else {
        damage = 0;
    }
    return damage;
}

float Destructible::heal(float amount) {
    m_hp += amount;
    if (m_hp > m_maxHp ) {
        amount -= m_hp-m_maxHp;
        m_hp = m_maxHp;
    }
    return amount;
}

void Destructible::die(Unit *owner) {
    // transform into a corpse
    owner->m_icon = '%';
    owner->m_color = TCODColor::darkRed;
    owner->m_name = m_corpseName;
    owner->blockMovement = false;

    // make sure corpses are drawn before living units
    engine.sendToBack(owner);
}

void MonsterDestructible::die(Unit *owner) {
    engine.gui->message(TCODColor::yellow, "%s is dead...", owner->m_name);
    Destructible::die(owner);
}

void PlayerDestructible::die(Unit *owner) {
    engine.gui->message(TCODColor::red, "You died !");
    Destructible::die(owner);
    // notify engine that game is over
    engine.gameStatus = Engine::DEFEAT;
}
