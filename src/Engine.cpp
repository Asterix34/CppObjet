#include "Engine.h"

Engine::Engine() : gameStatus(STARTUP), fovRadius(10)
{
    // create the game window
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);

    // instantiate new pointer to unit for player
    player = new Unit(40, 25, '@', TCODColor::white, "Player");

    // add player to the list of units
    units.push(player);

    // allocate new map
    gmap = new Map(80, 45);
}

Engine::~Engine()
{
    // awesome method to clean list of pointers
    units.clearAndDelete();
    // for every new we need a delete
    delete gmap;
}

// every frame you play
void Engine::update() {
    // var to store a key
    TCOD_key_t key;

    if (gameStatus == STARTUP) gmap->computeFov();
    gameStatus == IDLE;

    // check input event (event, *key, *mouse)
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);

    // game logic here
    int dx=0, dy=0;
    switch( key.vk ) {
        case TCODK_UP: dy=-1; break;
        case TCODK_DOWN: dy=1; break;
        case TCODK_LEFT: dx=-1; break;
        case TCODK_RIGHT: dx=1; break;
        default: break;
    }
    // if there is a move, compute FoV and make new turn
    if (dx !=0 ||dy != 0) {
        gameStatus = NEW_TURN;
        // only check now if move sent is valid
        if ( player->moveOrAttack(player->m_x + dx, player->m_y + dy) ) {
            gmap->computeFov();
        }
    }

    // logic for NEW_TURN
    if (gameStatus == NEW_TURN) {
        for (Unit **iterator = units.begin();
                iterator != units.end();
                iterator++) {
            Unit *unit = *iterator;
            if ( unit != player ) {
                unit->update();
            }
        }
    }

}

// render the current frame
void Engine::render() {
    // clear last frame
    TCODConsole::root->clear();
    // draw the map
    gmap->render();

    // draw units if in FoV
    for (Unit **iterator=units.begin(); // begin returns a pointer to first elem
        // an elem is a pointer to a unit, so pointer to pointer Unit **
        iterator != units.end(); iterator++) { // keep going until end
        Unit *unit = *iterator;
        // check if unit is in FoV
        if (gmap->isInFov(unit->m_x, unit->m_y) ) {
            unit->render(); // retrieve the unit pointer
        }

    }
}
