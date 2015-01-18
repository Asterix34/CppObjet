#include "Unit.h"
#include "Engine.h"

Unit::Unit()
{
    //ctor
}

Unit::Unit(int x, int y, char icon, const TCODColor &color, const char *name) :
    m_x(x), m_y(y), // position
    m_icon(icon), m_color(color), // appareance
    m_name(name) // and name
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
    printf("The %s growls!\n", m_name);
}

// will now decide if we move or attack form input
bool Unit::moveOrAttack(int x, int y) {
    if ( engine.gmap->isWall(x, y) ) return false; // false means wall

    for (Unit **iterator=engine.units.begin();
            iterator != engine.units.end();
            iterator++) {
        Unit *unit = *iterator;

        // if
        if ( unit->m_x == x && unit->m_y == y ) {
            printf("The %s laughs at your puny efforts to attack him !\n", unit->m_name);
            return false; // still false for attack
        }
    }

    this->m_x = x;
    this->m_y = y;
    return true; // player moved
}
