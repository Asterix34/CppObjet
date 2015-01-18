#include "Unit.h"

Unit::Unit()
{
    //ctor
}

Unit::Unit(int x, int y, char icon, const TCODColor &color, const char *name) :
    m_x(x), m_y(y), // position
    m_icon(icon), m_color(color), // appareance
    m_name(name), // and name
    blockMovement(true), attacker(NULL),
    destructible(NULL), ai(NULL)
{
    // if we stored as string we would have instead :
    // strcpy(this->name, name);
}

Unit::~Unit()
{
    //dtor
}

void Unit::render() const {
    TCODConsole::root->setChar(m_x, m_y, m_icon);
    TCODConsole::root->setCharForeground(m_x, m_y, m_color);
}

void Unit::update() {
    if ( ai ) ai->update(this); // delegate with composition
}
