#include <iostream>
using namespace std;

// external libs
#include "libtcod.hpp"

// my classes
#include "Unit.h"


/* legacy block */
#include "Personnage.h"
#include "Objet.h"

Personnage *joueur;
/* end legacy block */

int main() {
    /* legacy block */
    joueur = new Personnage("Asterix");

    /* end legacy block */

    // start player
    Unit player(40, 25, '@');

    // create the game window
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);

    // game loop
    while ( !TCODConsole::isWindowClosed() ) {
        // check input event
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,NULL,NULL);

        // clear last frame
        TCODConsole::root->clear();

        // compute frame here
        // add a char to the frame in X,Y,Char
        TCODConsole::root->putChar(player.m_x,player.m_y,player.m_icon);
        // generate and display console frame
        TCODConsole::flush();
    }
    return 0;
}
