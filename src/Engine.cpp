#include "Engine.h"

Engine::Engine() : fovRadius(10), computeFov(true)
{
    // create the game window
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);

    // instantiate new pointer to unit for player
    player = new Unit(40, 25, '@', TCODColor::white);

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

    // check input event (event, *key, *mouse)
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS,&key,NULL);

    // game logic here
    // check which key is pressed and change coordinates of player
    switch(key.vk) {
        case TCODK_UP :
            if ( ! gmap->isWall(player->m_x,player->m_y-1)) {
                player->m_y--;
                computeFov=true;
            }
        break;
        case TCODK_DOWN :
            if ( ! gmap->isWall(player->m_x,player->m_y+1)) {
                player->m_y++;
                computeFov=true;
            }
        break;
        case TCODK_LEFT :
            if ( ! gmap->isWall(player->m_x-1,player->m_y)) {
                player->m_x--;
                computeFov=true;
            }
        break;
        case TCODK_RIGHT :
            if ( ! gmap->isWall(player->m_x+1,player->m_y)) {
                player->m_x++;
                computeFov=true;
            }
        break;
        default: break;
    }
    // compute FoV if enabled
    if ( computeFov ) {
        gmap->computeFov();
        computeFov = false;
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
