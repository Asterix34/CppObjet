#ifndef ENGINE_H
#define ENGINE_H

#include "main.hpp"

class Engine
{
    public:
        int screenWidth, screenHeight;
        Gui *gui; // pointer allow easier initialization of dependent values

        TCODList<Unit *> units; // list of units - dead or alive
        Unit *player;
        Map *gmap;
        enum GameStatus { STARTUP, IDLE, NEW_TURN, VICTORY, DEFEAT } gameStatus;
        int fovRadius; // radius in nb of tiles for FoV

        TCOD_key_t lastKey; // store last key pressed
        TCOD_mouse_t mouse;

        Engine(int screenWidth, int screenHeight);
        virtual ~Engine();

        void update();
        void render();

        void sendToBack(Unit *unit);

        Unit *getClosestMonster(int x, int y, float range) const;
    protected:
    private:
        bool computeFov; // expensive ressource wise so do it only when player moves
};

// indicate that it has been declared somewhere else
extern Engine engine;

#endif // ENGINE_H
