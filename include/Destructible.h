#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

#include "main.hpp"

class Destructible
{
    public:
        float m_maxHp; // maximum health points
        float m_hp; // current health points
        float m_defense; // dmg mitigation
        const char *m_corpseName; // the name of destroyed unit

        Destructible(float maxHp, float defense, const char *corpseName);
        virtual ~Destructible();

        bool isDead() const;
        // health management
        float takeDamage(Unit *owner, float damage);
        float heal(float amount);
        virtual void die(Unit *owner);
    protected:
    private:
};

class MonsterDestructible : public Destructible {
public :
    MonsterDestructible(float maxHp, float defense, const char *corpseName);
    void die(Unit *owner);
};

class PlayerDestructible : public Destructible {
public :
    PlayerDestructible(float maxHp, float defense, const char *corpseName);
    void die(Unit *owner);
};

#endif // DESTRUCTIBLE_H
