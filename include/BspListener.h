#ifndef BSPLISTENER_H
#define BSPLISTENER_H

#include "Map.h"

class BspListener : public ITCODBspCallback // interface
{
    public:
        BspListener(Map &gmap);
        virtual ~BspListener();
        int roomNum; // room number // here for DEBUG
        bool visitNode(TCODBsp *node, void *userData);
    protected:
    private:
        Map &gmap; // a map to dig

        int lastX, lastY; // center of the last room
};

#endif // BSPLISTENER_H
