#ifndef UNIT_H
#define UNIT_H

#include <stdio.h>
#include "main.hpp"


class Unit
{
    public:
        Unit();
        Unit(int x, int y, char icon, const TCODColor &color, const char *name);
        virtual ~Unit();
        int m_x, m_y; // coords
        char m_icon; // icon
        TCODColor m_color; // color
        const char *m_name; // name of unit - can't be changed after instanciation

        bool blockMovement; // can we walk on this
        Attacker *attacker; // something that deals damages
        Destructible *destructible; // something that can be damaged
        Ai *ai; // something self updating

        void render() const; // method to send the unit to output

        void update();

    protected:
    private:
};

#endif // UNIT_H
