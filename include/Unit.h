#ifndef UNIT_H
#define UNIT_H

#include "libtcod.hpp"

class Unit
{
    public:
        Unit();
        Unit(int x, int y, char icon, const TCODColor &color);
        virtual ~Unit();
        int m_x, m_y; // coords
        char m_icon; // icon
        TCODColor m_color; // color
        void render() const; // method to send the unit to output
    protected:
    private:
};

#endif // UNIT_H
