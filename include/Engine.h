#ifndef ENGINE_H
#define ENGINE_H

#include "libtcod.hpp"

#include "Unit.h"
#include "Map.h"

class Engine
{
    public:
        TCODList<Unit *> units;
        Unit *player;
        Map *gmap;

        Engine();
        virtual ~Engine();

        void update();
        void render();
    protected:
    private:
};

// indicate that it has been declared somewhere else
extern Engine engine;

#endif // ENGINE_H
