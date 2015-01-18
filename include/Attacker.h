#ifndef ATTACKER_H
#define ATTACKER_H

#include "main.hpp"

class Attacker
{
    public:
        float m_power; // damage given

        Attacker(float power);
        virtual ~Attacker();

        void attack(Unit *owner, Unit *target);
    protected:
    private:
};

#endif // ATTACKER_H
