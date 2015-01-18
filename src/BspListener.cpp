#include "BspListener.h"
#include "Map.h"

BspListener::BspListener(Map &gmap) :
    gmap(gmap), roomNum(0)
{
    //ctor
}

BspListener::~BspListener()
{
    //dtor
}

bool BspListener::visitNode(TCODBsp *node, void *userData) {
    if (node->isLeaf()) { // oh look a composite
        int x, y, w, h; // coords and size
        TCODRandom *rng = TCODRandom::getInstance();
        w = rng->getInt(ROOM_MINH_SIZE, node->w-2); // get random size
        h = rng->getInt(ROOM_MINV_SIZE, node->w-2); // from min to generated
        x = rng->getInt(node->x+1, node->x + node->w - w-1); // get random pos
        y = rng->getInt(node->y+1, node->y + node->h - h-1); // from pos to max

        // now make a room
        gmap.createRoom(x, y, x+w-1, y+h-1, roomNum==0, roomNum);

        // if it's not the first room, we need a corridor
        if ( roomNum ) { // if >0 then true
            gmap.dig(lastX, lastY, x + w/2, lastY);
            gmap.dig(x + w/2, lastY, x + w/2, y + h/2);
        }

        // store current pos (center) for next node
        lastX = x + w/2;
        lastY = y + h/2;
        roomNum++;

        return true;// true allow to keep visiting
    }
    return false;  // false would break the loop
}
