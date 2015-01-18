#include "libtcod.hpp"

#include "Map.h"
#include "BspListener.h"
#include "Engine.h"

Map::Map(int width, int height) : width(width), height(height)
{
    // list of tiles in map
    tiles = new Tile[width*height];

    // make new BSP root node
    TCODBsp bsp(0, 0, width, height);

    // start generation - (TCODRandom *randomizer, int nb, int minHSize,
    //                      int minVSize, float maxHRatio, float maxVRatio);
    bsp.splitRecursive(NULL, 8, ROOM_MINH_SIZE, ROOM_MINV_SIZE, 1.5f, 1.5f);

    // create a listener
    BspListener listener(*this);

    // traverse the BSP tree - check doc
    bsp.traverseInvertedLevelOrder(&listener,NULL);

}

Map::~Map()
{
   delete [] tiles;
}

// simple method to check if a tile is a wall
bool Map::isWall(int x, int y) const {
    return tiles[x+y*width].isWall; // return the boolean attribute
}

// render the map
void Map::render() const {
    // default const for colors
    static const TCODColor darkWall(0,0,100);
    static const TCODColor darkGround(50,50,150);

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {
            // ternary conditional operator ?:;
            TCODConsole::root->setCharBackground(x, y,
                 isWall(x, y) ? darkWall : darkGround
            );
        }

    }
}

// dig
void Map::dig(int x1, int y1, int x2, int y2) {
    // x2 must be > x1
    if (x2 < x1) {
        int tmp=x2;
        x2 = x1;
        x1 = tmp;
    }
    if (y2 < y1) {
        int tmp=y2;
        y2 = x1;
        y1 = tmp;
    }
    // change every tile in the range
    for (int tileX=x1; tileX <= x2; tileX++) {
        for (int tileY=y1; tileY <= y2; tileY++) {
            tiles[tileX+tileY*width].isWall=false;
        }
    }
}

// now create a room with mechanics (units)
void Map::createRoom(int x1, int y1, int x2, int y2, bool first, int nb) {
    dig(x1, y1, x2, y2);
    if ( first ) {
        // spawn player in first room
        engine.player->m_x=(x1+x2)/2;
        engine.player->m_y=(y1+y2)/2;
    } else {
        // we use random lib from TCOD
        TCODRandom *rng = TCODRandom::getInstance(); // oh look a singleton
        if ( rng->getInt(0, 0) == 0 ) { // should proc 25% chance
            // add a NPC to the room
            engine.units.push( new Unit((x1+x2)/2, (y1+y2)/2, nb+48, TCODColor::yellow));
        }
    }
}
