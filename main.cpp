#include <iostream>
using namespace std;

// external libs
#include "main.hpp"


// global engine (called as extern in Engine.h)
Engine engine(80, 50); // width, height

int main() {
    // game loop
    while ( !TCODConsole::isWindowClosed() ) {
        engine.update();
        engine.render();

        // generate and display console frame
        TCODConsole::flush();
    }
    return 0;
}
