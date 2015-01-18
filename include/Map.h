#ifndef MAP_H
#define MAP_H

#include "main.hpp"

// some const
const int ROOM_MIN_SIZE = 4;
const int ROOM_MAX_SIZE = 12;
const int ROOM_MAX_MONSTERS = 3;
const int ROOM_MAX_ITEMS = 2;

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

        void render() const;

        bool isWall(int x, int y) const;
        bool canWalk(int x, int y) const; // will check if wall and if someone in the tile

        // FOV management
        bool isInFov(int x, int y) const;
        bool isExplored(int x, int y) const;
        void computeFov();

        // NPC management
        void addMonster(int x, int y);

        // items management
        void addItem(int x, int y);
        // void addContainer(int x, int y); TODO
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
