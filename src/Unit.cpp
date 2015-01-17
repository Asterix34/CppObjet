#include "Unit.h"

Unit::Unit()
{
    //ctor
}

Unit::Unit(int x, int y, char icon, const TCODColor &color) :
    m_x(x), m_y(y), // position
    m_icon(icon), m_color(color) // appareance
{

}

Unit::~Unit()
{
    //dtor
}

void Unit::render() const {
    TCODConsole::root->setChar(m_x, m_y, m_icon);
    TCODConsole::root->setCharForeground(m_x, m_y, m_color);
}
