#include "Map.h"
#include "BspListener.h"

Map::Map(int width, int height) : width(width), height(height)
{
    // list of tiles in map
    tiles = new Tile[width*height];
    tmap = new TCODMap(width, height);

    // make new BSP root node
    TCODBsp bsp(0, 0, width, height);

    // start generation - (TCODRandom *randomizer, int nb, int minHSize,
    //                      int minVSize, float maxHRatio, float maxVRatio);
    bsp.splitRecursive(NULL, 16, ROOM_MAX_SIZE, ROOM_MAX_SIZE, 1.5f, 1.5f);

    // create a listener
    BspListener listener(*this);

    // traverse the BSP tree - check doc
    bsp.traverseInvertedLevelOrder(&listener,NULL);

}

Map::~Map()
{
   delete [] tiles;
   delete tmap;
}

// check if a tile can be walked
bool Map::canWalk(int x, int y) const {
    if (isWall(x, y)) {
        return false; // can't walk on a wall noob
    }
    // now parse every unit in the map, and see if one is where we try to walk
    for (Unit **iterator = engine.units.begin();
            iterator != engine.units.end();
            iterator++) {
        Unit *unit = *iterator; // remember iterator is a pointer to a pointer to a unit
        if ( unit->blockMovement && unit->m_x == x && unit->m_y == y) {
            // there is a unit here that block movement
            return false;
        }
    }
    // if everything gone good, then walk
    return true;
}

// simple method to check if a tile is a wall
bool Map::isWall(int x, int y) const {
    return !tmap->isWalkable(x, y); // return the boolean attribute
}

// simple method to check if a tile has been explored
bool Map::isExplored(int x, int y) const {
    return tiles[x + y*width].explored; // return the boolean attribute
}

// check if a node has been explored
bool Map::isInFov(int x, int y) const {
    // add to prevent out of map numbers - for mouse
    if ( x<0 || x>=width || y<0 || y>=height )
        return false;

    if ( tmap->isInFov(x, y) ) {
        tiles[x + y*width].explored = true; // is this still useful ?
        return true;
    }
    return false;
}

// check if a node is in Fov and in range (0 = no limit)
bool Map::isInFovAndRange(int x, int y, float maxRange) const {
    if (isInFov(x, y)) {
        if( maxRange == 0 || engine.player->getDistance(x, y) <= maxRange ) {
            return true;
        }
    }
    return false;
}

void Map::computeFov() {
    tmap->computeFov(engine.player->m_x, engine.player->m_y, engine.fovRadius);
}

// render the map
void Map::render() const {
    // default const for colors
    static const TCODColor darkWall(0,0,100);
    static const TCODColor darkGround(50,50,150);
    static const TCODColor lightWall(130,110,50);
    static const TCODColor lightGround(200,180,50);

    for (int x=0; x<width; x++) {
        for (int y=0; y<height; y++) {

            if ( isInFov(x, y) ) {
                // ternary conditional operator ?:;
                TCODConsole::root->setCharBackground(x, y,
                    isWall(x, y) ? lightWall : lightGround
                );
            } else if ( isExplored(x, y) ) {
                TCODConsole::root->setCharBackground(x, y,
                    isWall(x, y) ? darkWall : darkGround
                );
            } // else ?

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
        y2 = y1;
        y1 = tmp;
    }
    // change every tile in the range
    for (int tileX=x1; tileX <= x2; tileX++) {
        for (int tileY=y1; tileY <= y2; tileY++) {
            tmap->setProperties(tileX, tileY, true, true); // now use TCODMap
        }
    }
}

// now create a room with mechanics (units)
void Map::createRoom(int x1, int y1, int x2, int y2, bool first) {
    dig(x1, y1, x2, y2);
    if ( first ) {
        // spawn player in first room
        engine.player->m_x=(x1+x2)/2;
        engine.player->m_y=(y1+y2)/2;
    } else {
        // we use random lib from TCOD
        TCODRandom *rng = TCODRandom::getInstance(); // oh look a singleton
        int nbMonsters = rng->getInt(0, ROOM_MAX_MONSTERS);
        while ( nbMonsters > 0) {
            int x = rng->getInt(x1, x2);
            int y = rng->getInt(y1, y2);
            if ( canWalk(x, y) ) {
                addMonster(x, y);
                nbMonsters--;
            }
        }

        // add items
        int nbItems=rng->getInt(0,ROOM_MAX_ITEMS);
        while (nbItems > 0) {
            int x=rng->getInt(x1,x2);
            int y=rng->getInt(y1,y2);
            if ( canWalk(x,y) ) {
                addItem(x,y);
            }
            nbItems--;
        }
    }
}

void Map::addMonster(int x, int y) {
    TCODRandom *rng = TCODRandom::getInstance();

    Unit *monster;

    if ( rng->getInt(0, 100) < 80 ) {
        // create an orc (80%)
        monster = new Unit(x, y, 'O', TCODColor::desaturatedGreen, "Orc");
        monster->destructible = new MonsterDestructible(10, 0, "Dead orc");
        monster->attacker = new Attacker(3);
        monster->ai = new MonsterAi();
    } else {
        // create a troll
        monster = new Unit(x, y, 'T', TCODColor::darkerGreen, "Troll");
        monster->destructible = new MonsterDestructible(16, 1, "Troll carcass");
        monster->attacker = new Attacker(4);
        monster->ai = new MonsterAi();
    }
    engine.units.push( monster );
}

void Map::addItem(int x, int y) {
    TCODRandom *rng = TCODRandom::getInstance();

    int dice = rng->getInt(0, 100);
    Unit *item;

    if ( dice < 50 ) { // 50%
        // create health potion
        item = new Unit(x, y, '!', TCODColor::violet, "Health Potion");
        item->blockMovement = false;
        item->pickable = new Healer(10);
    } else if ( dice < 50+20 ) { // 20%
        // create lightning scroll
        item = new Unit(x, y, '#', TCODColor::lightBlue, "Scroll of Lightning Bolt");
        item->blockMovement = false;
        item->pickable = new LightningBolt(5,20);
    }
    else if ( dice < 50+20+20 ) { // 20%
        // create lightning scroll
        item = new Unit(x, y, '#', TCODColor::orange, "Scroll of Fireball");
        item->blockMovement = false;
        item->pickable = new Fireball(5,20);
    }
    engine.units.push(item);
}
