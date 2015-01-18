#include "libtcod.hpp"

#include "Map.h"


Map::Map(int width, int height) : width(width), height(height)
{
    // list of tiles in map
    tiles = new Tile[width*height];

    // add random walls
    setWall(30, 22);
    setWall(50, 22);
}

Map::~Map()
{
   delete [] tiles;
}

// simple method to check if a tile is a wall
bool Map::isWall(int x, int y) const {
    return tiles[x+y*width].isWall; // return the boolean attribute
}

// change a tile to a wall
void Map::setWall(int x, int y) {
    tiles[x+y*width].isWall = true;
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
