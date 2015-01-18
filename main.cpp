#include <iostream>
using namespace std;

// external libs
#include "main.hpp"

/* legacy block */
#include "Personnage.h"
#include "Objet.h"
Personnage *joueur;
/* end legacy block */

// global engine (called as extern in Engine.h)
Engine engine(80, 50); // width, height



int main() {
    /* legacy block */
    joueur = new Personnage("Asterix");
    /* end legacy block */

    // game loop
    while ( !TCODConsole::isWindowClosed() ) {
        engine.update();
        engine.render();

        // generate and display console frame
        TCODConsole::flush();
    }
    return 0;
}
