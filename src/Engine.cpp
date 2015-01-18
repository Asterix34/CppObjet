#include "Engine.h"
// #include <Windows.h>

Engine::Engine(int screenWidth, int screenHeight) :
    screenWidth(screenWidth), screenHeight(screenHeight),
    gameStatus(STARTUP), fovRadius(10)
{
    // create the game window
    TCODConsole::initRoot(80,50,"libtcod C++ tutorial",false);

    // instantiate new pointer to unit for player
    player = new Unit(40, 25, '@', TCODColor::white, "Player");
    player->destructible = new PlayerDestructible(30, 2, "Your cadaver"); // 30 hp and 2def
    player->attacker = new Attacker(5); // starting damage 5
    player->ai = new PlayerAi();
    player->container = new Container(10);

    // add player to the list of units
    units.push(player);

    // allocate new map and the gui
    gmap = new Map(80, 45);
    gui = new Gui();

    gui->message(TCODColor::white,
        "Welcome stranger!\nPrepare to perish in the Tombs of the Ancient Kings.");

}

Engine::~Engine()
{
    // awesome method to clean list of pointers
    units.clearAndDelete();
    // for every new we need a delete
    delete gmap;
    delete gui;
}

// every frame you play
void Engine::update() {

    if (gameStatus == STARTUP) {
            gmap->computeFov();
    }

    gameStatus = IDLE;

    // check input event (event|..., *key, *mouse)
    TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS|TCOD_EVENT_MOUSE,&lastKey,&mouse);

    //Sleep(10);

    // game logic here
    player->update();

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
    // has this been done already in unit ?
    player->render();

    gui->render();
}

void Engine::sendToBack(Unit *unit) {
    // this will put pointer on top of list
    units.remove(unit);
    units.insertBefore(unit, 0);
}

Unit *Engine::getClosestMonster(int x, int y, float range) const {
    Unit *closest = NULL;
    float bestDistance = 1E6f;

    // loop all units
    for (Unit **it = units.begin();
            it != units.end(); it++) {
        Unit *unit = *it;
        if ( unit != player && unit->destructible
             && !unit->destructible->isDead() ) {
            float distance = unit->getDistance(x, y);
            if ( distance < bestDistance
                    && (distance <= range || range == 0.0f )) {
                bestDistance = distance;
                closest = unit;
            }
        }
    }
    return closest;
}
