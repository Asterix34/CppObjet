#ifndef MAP_H
#define MAP_H

#include "libtcod.hpp"


// some const
const int ROOM_MINH_SIZE = 12;
const int ROOM_MINV_SIZE = 4;

struct Tile {
    bool isWall; // is this tile a wall ?
    Tile() : isWall(true) {} // default ctor - now all walls
};

class Map
{
    public:
        int width, height; // size of the map

        // ctor and dtor
        Map(int width, int height);
        virtual ~Map();

        bool isWall(int x, int y) const;
        void render() const;

    protected:
        // map of tiles
        Tile *tiles;

        void dig(int x1, int y1, int x2, int y2); // can dig rooms
        void createRoom(int x1, int y1, int x2, int y2, bool first, int nb);

        // BSP is Binary Space Partition, it generate tree like a dungeon with rooms
        friend class BspListener;
    private:
};

#endif // MAP_H
