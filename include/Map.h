#ifndef MAP_H
#define MAP_H

#include "libtcod.hpp"

// some const
const int ROOM_MIN_SIZE = 4;
const int ROOM_MAX_SIZE = 12;

struct Tile {
    bool explored; // has this tile been explored ?
    Tile() : explored(false) {} // default ctor
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

        // FOV management
        bool isInFov(int x, int y) const;
        bool isExplored(int x, int y) const;
        void computeFov();

    protected:
        // map of tiles
        Tile *tiles;
        TCODMap *tmap; // we now use TCODMap from framework (handles more)

        void dig(int x1, int y1, int x2, int y2); // can dig rooms
        void createRoom(int x1, int y1, int x2, int y2, bool first);

        // BSP is Binary Space Partition, it generate tree like a dungeon with rooms
        friend class BspListener;
    private:
};

#endif // MAP_H
