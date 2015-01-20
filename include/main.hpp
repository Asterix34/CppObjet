#ifndef MAIN_HPP_INCLUDED
#define MAIN_HPP_INCLUDED

/* debug */
const bool disableFoV = true;

#include "libtcod.hpp"
// so to let it compile we need to inform the compiler a class Unit will exist
// i know this is a prototype in a prototype but blame C++
class Unit;
class Destructible;
class Attacker;
class Ai;
class Pickable;
class Container;
class Map;
class Gui;

#include "Destructible.h"
#include "Attacker.h"
#include "Ai.h"
#include "Pickable.h"
#include "Container.h"
#include "Unit.h"
#include "Map.h"
#include "Gui.h"
#include "Engine.h"


#endif // MAIN_HPP_INCLUDED
