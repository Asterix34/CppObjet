#include "BspListener.h"

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
        // dig a room
        int x, y, w, h; // coords and size
        TCODRandom *rng = TCODRandom::getInstance();
        w = rng->getInt(ROOM_MIN_SIZE, node->w-2); // get random size
        h = rng->getInt(ROOM_MIN_SIZE, node->w-2); // from min to generated
        x = rng->getInt(node->x+1, node->x + node->w - w-1); // get random pos
        y = rng->getInt(node->y+1, node->y + node->h - h-1); // from pos to max

        //printf("[%d] : X=%d | Y=%d | W=%d | H=%d\n", roomNum, x, y, w, h);

        // this prevent the out of range
        bool error = false;
        if (x<1) {
            x=1; error = true;
        }
        if (y<1) {
            y=1; error = true;
        }
        if (x+w > gmap.width) {
            w = gmap.width - x - 1; error = true;
        }
        if (y+h > gmap.height) {
            h = gmap.height - y - 1; error = true;
        }

        /*if (error) {
            printf("ERROR out of range, preventing...");
            printf("[%d] : X=%d | Y=%d | W=%d | H=%d\n", roomNum, x, y, w, h);
        }*/

        // now that x,y,w,h guaranteed to be in range, make room
        gmap.createRoom(x, y, x+w-1, y+h-1, roomNum==0);

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
