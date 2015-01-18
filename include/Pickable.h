#ifndef PICKABLE_H
#define PICKABLE_H

#include "main.hpp"

class Pickable
{
    public:
        Pickable();
        virtual ~Pickable();

        bool pick(Unit *owner, Unit *wearer);
        // use is virtual to be overriden by items (units)
        virtual bool use(Unit *owner, Unit *wearer);
    protected:
    private:
};

class Healer : public Pickable
{
    public:
        float amount; // how many hp to restore

        Healer(float amount);
        virtual ~Healer();

        bool use(Unit *owner, Unit *wearer);
    protected:
    private:
};

class LightningBolt : public Pickable {
    public:
        float range, damage;
        LightningBolt(float range, float damage);
        bool use(Unit *owner, Unit *wearer);
};


#endif // PICKABLE_H
