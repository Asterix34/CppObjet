#include "Ai.h"
#include <cmath>

void PlayerAi::update(Unit *owner) {
    if ( owner->destructible && owner->destructible->isDead() ) {
        return;
    }

    int dx=0, dy=0;

    switch( engine.lastKey.vk ) {
        case TCODK_UP: dy=-1; break;
        case TCODK_DOWN: dy=1; break;
        case TCODK_LEFT: dx=-1; break;
        case TCODK_RIGHT: dx=1; break;
        default: break;
    }
    // if there is a move, compute FoV and make new turn
    if (dx !=0 || dy != 0) {
        engine.gameStatus = Engine::NEW_TURN;

        // only check now if move sent is valid
        if ( moveOrAttack(owner, owner->m_x + dx, owner->m_y + dy) ) {
            engine.gmap->computeFov();
        }
    }
}


// will now decide if we move or attack form input
bool PlayerAi::moveOrAttack(Unit *owner, int x, int y) {
    if ( engine.gmap->isWall(x, y) ) return false; // false means wall

    // look for living units to attack
    for (Unit **iterator=engine.units.begin();
            iterator != engine.units.end();
            iterator++) {
        Unit *unit = *iterator;

        // if
        if ( unit->destructible && !unit->destructible->isDead()
                && unit->m_x == x && unit->m_y == y ) {

            owner->attacker->attack(owner, unit);
            return false; // still false for attack
        }
    }

    // look for a corpse
    for (Unit **iterator=engine.units.begin();
            iterator != engine.units.end();
            iterator++) {
        Unit *unit = *iterator;
        if ( unit->destructible && unit->destructible->isDead()
                && unit->m_x == x && unit->m_y == y ) {
            engine.gui->message(TCODColor::white, "There's a %s here.", unit->m_name);
        }
    }

    owner->m_x = x;
    owner->m_y = y;
    return true; // player moved
}

/* Monster AI */
// allow monster to track player when no longer in FoV
static const int TRACKING_TURNS = 3;


void MonsterAi::update(Unit *owner) {
    // is it alive ?
    if ( owner->destructible && owner->destructible->isDead() ) {
        return;
    }

    // move to player if in FoV
    if ( engine.gmap->isInFov(owner->m_x, owner->m_y ) ) {
        // we can see the player, so we flag him for moving
        // (max X turns after out of sight)
        moveCount = TRACKING_TURNS;
    } else if ( moveCount > 0 ) {
        moveCount--;
    }
    // if player flagged, move towards him
    if ( moveCount ) {
        moveOrAttack(owner, engine.player->m_x, engine.player->m_y); // won't this move too fast ?
    }
}

void MonsterAi::moveOrAttack(Unit *owner, int targetX, int targetY) {
    int dx = targetX - owner->m_x;
    int dy = targetY - owner->m_y;
    // let's add some numbers to slide on walls
    int stepdx = (dx > 0 ? 1 : -1);
    int stepdy = (dy > 0 ? 1 : -1);

    float distance = sqrtf( dx * dx + dy * dy); // euclidian distance

    if ( distance >= 2 ) { //out of melee range
        // very basic path finding for monsters (idiot monsters anyway)
        dx = (int)(round( dx / distance ));
        dy = (int)(round( dy / distance ));
        // TODO check if it can go diagonal - should not happen

        if ( engine.gmap->canWalk( owner->m_x + dx, owner->m_y + dy ) ) {
            // if it's walkable walk
            owner->m_x += dx;
            owner->m_y += dy;
        } else if ( engine.gmap->canWalk( owner->m_x + stepdx, owner->m_y ) ) {
            owner->m_x += stepdx;
        } else if ( engine.gmap->canWalk( owner->m_x, owner->m_y + stepdy ) ) {
            owner->m_y += stepdy;
        }
    } else if ( owner->attacker ) {
        owner->attacker->attack( owner, engine.player );
    }
}
