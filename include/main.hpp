#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED


// external libs
#include "libtcod.hpp"

// so to let it compile we need to inform the compiler a class Unit will exist
// i know this is a prototype in a prototype but blame C++
class Unit;
class Ai;
class Attacker;
class Map;
class Destructible;

#include "Destructible.h"
#include "Attacker.h"
#include "Ai.h"
#include "Unit.h"
#include "Map.h"
#include "Engine.h"

#endif // MAIN_HPP_INCLUDED
