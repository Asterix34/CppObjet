#ifndef MAP_H
#define MAP_H

struct Tile {
    bool isWall; // is this tile a wall ?
    Tile() : isWall(false) {} // default ctor
};

class Map
{
    public:
        int width, height; // size of the map

        // ctor and dtor
        Map(int width, int height);
        virtual ~Map();

        bool isWall(int x, int y) const;
        void render() const; // decorator pattern

    protected:
        // map of tiles
        Tile *tiles;

        void setWall(int x, int y); // add a new wall
    private:
};

#endif // MAP_H
