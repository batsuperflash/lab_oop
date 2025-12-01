#ifndef NPC_TYPES_H
#define NPC_TYPES_H

#include "NPC.h"

class Visitor;

class Dragon : public NPC {
public:
    Dragon(std::string n, double x, double y) : NPC(n, x, y) {}
    std::string getType() const override { return "Dragon"; }
    bool acceptFight(Visitor& v, NPC& other) override;
};

class Frog : public NPC {
public:
    Frog(std::string n, double x, double y) : NPC(n, x, y) {}
    std::string getType() const override { return "Frog"; }
    bool acceptFight(Visitor& v, NPC& other) override;
};

class Knight : public NPC {
public:
    Knight(std::string n, double x, double y) : NPC(n, x, y) {}
    std::string getType() const override { return "Knight"; }
    bool acceptFight(Visitor& v, NPC& other) override;
};

#endif
