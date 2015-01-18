#include "Unit.h"
#include <math.h>

Unit::Unit()
{
    //ctor
}

Unit::Unit(int x, int y, char icon, const TCODColor &color, const char *name) :
    m_x(x), m_y(y), // position
    m_icon(icon), m_color(color), // appareance
    m_name(name), // and name
    blockMovement(true), attacker(NULL), // block and can attack
    destructible(NULL), ai(NULL), // can be destroyed, has an ai
    pickable(NULL), container(NULL) // can be picked, contains items
{
    // if we stored name as string we would have instead :
    // strcpy(this->name, name);
}

Unit::~Unit()
{
    if ( attacker ) delete attacker;
    if ( destructible ) delete destructible;
    if ( ai ) delete ai;
    if ( pickable ) delete pickable;
    if ( container ) delete container;
}

void Unit::render() const {
    TCODConsole::root->setChar(m_x, m_y, m_icon);
    TCODConsole::root->setCharForeground(m_x, m_y, m_color);
}

void Unit::update() {
    if ( ai ) ai->update(this); // delegate with composition
}

float Unit::getDistance(int cx, int cy) const {
    int dx=m_x-cx;
    int dy=m_y-cy;
    return sqrtf(dx*dx+dy*dy);
}
