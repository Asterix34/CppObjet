#ifndef ENGINE_H
#define ENGINE_H

#include "Unit.h"
#include "Map.h"

class Engine
{
    public:
        TCODList<Unit *> units;
        Unit *player;
        Map *gmap;
        enum GameStatus { STARTUP, IDLE, NEW_TURN, VICTORY, DEFEAT } gameStatus;

        int fovRadius;

        Engine();
        virtual ~Engine();

        void update();
        void render();
    protected:
    private:
        bool computeFov; // expensive ressource wise so do it only when player moves
};

// indicate that it has been declared somewhere else
extern Engine engine;

#endif // ENGINE_H
