#include "BspListener.h"
#include <math.h>

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
 /*       TCODRandom *rng = TCODRandom::getInstance();
        w = rng->getInt(node->w-2-EMPTY_MAX_SIZE, node->w-2); // get random size
        h = rng->getInt(node->h-2-EMPTY_MAX_SIZE, node->h-2); // from min to generated
        x = rng->getInt(node->x+1, node->x + node->w - w-1); // get random pos
        y = rng->getInt(node->y+1, node->y + node->h - h-1); // from pos to max
*/
        w = node->w-1;
        h = node->h-1;
        x = node->x+1;
        y = node->y+1;
        printf("[%d] : X=%d | Y=%d | W=%d | H=%d\n", roomNum, x, y, w, h);

        // this prevent the out of range
        bool error = false;
        if (x<0) {
            x=0; error = true;
        }
        if (y<0) {
            y=0; error = true;
        }
        if (x+w > gmap.width) {
            w = gmap.width - x - 1; error = true;
        }
        if (y+h > gmap.height) {
            h = gmap.height - y - 1; error = true;
        }

        if (error) {
            printf("ERROR out of range, preventing...");
            printf("[%d] : X=%d | Y=%d | W=%d | H=%d\n", roomNum, x, y, w, h);
        }

        // calculate sizeMult for more items and monster in big rooms
        int sizeMult = node->w * node->h / 200;
        printf("Node is w=%d, h=%d, sM=%d \n", node->w, node->h, sizeMult);
        if (sizeMult < 1) sizeMult = 1;

        // now that x,y,w,h guaranteed to be in range, make room
        gmap.createRoom(x, y, x+w-1, y+h-1, roomNum==0, sizeMult);

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
