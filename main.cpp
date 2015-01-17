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
    Unit player(40, 25, '@', TCODColor::white);

    // create the game window
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);

    // game loop
    while ( !TCODConsole::isWindowClosed() ) {
        // var to store a key
        TCOD_key_t key;

        // check input event (event, *key, *mouse)
        TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);

        // game logic here
        // check which key is pressed and change coordinates
        switch(key.vk) {
            case TCODK_UP : player.m_y--; break;
            case TCODK_DOWN : player.m_y++; break;
            case TCODK_LEFT : player.m_x--; break;
            case TCODK_RIGHT : player.m_x++; break;
            default: break;
        }


        // clear last frame
        TCODConsole::root->clear();

        // compute frame here

        // render the unit
        player.render();

        // generate and display console frame
        TCODConsole::flush();
    }
    return 0;
}
