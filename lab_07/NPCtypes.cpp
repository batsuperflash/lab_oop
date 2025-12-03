#include "NPCtypes.h"
#include "dungeon.h"

// Определения acceptFight, чтобы vtable был
bool Dragon::acceptFight(Visitor& v, NPC& other) { return false; }
bool Knight::acceptFight(Visitor& v, NPC& other) { return false; }
bool Frog::acceptFight(Visitor& v, NPC& other) { return false; }
