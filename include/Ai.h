#ifndef AI_H
#define AI_H

#include "main.hpp"

class Ai
{
    public:
        virtual void update(Unit *owner) = 0; // this makes the class abstract
};

class PlayerAi : public Ai {
    public:
        void update(Unit *owner);
    protected:
        bool moveOrAttack(Unit *owner, int targetX, int targetY);
};

class MonsterAi : public Ai {
    public:
        void update(Unit *owner);
    protected:
        int moveCount;
        void moveOrAttack(Unit *owner, int targetX, int targetY);
};

#endif // AI_H
