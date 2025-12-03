#pragma once
#include <string>
#include <memory>
#include <cmath>
#include <random>

class Visitor;

class NPC {
protected:
    std::string name;
    double x{}, y{};
    bool alive{true};

public:
    NPC(std::string n, double x, double y) : name(std::move(n)), x(x), y(y) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    std::string getName() const { return name; }
    double getX() const { return x; }
    double getY() const { return y; }

    bool isAlive() const { return alive; }
    void kill() { alive = false; }

    double distanceTo(const NPC& other) const {
        return std::sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
    }

    virtual bool acceptFight(Visitor& v, NPC& other) = 0;

    int attack() const { return rand()%6 + 1; }
    int defense() const { return rand()%6 + 1; }

    void move(double dx, double dy) {
        if(!alive) return;
        x += dx;
        y += dy;
        if(x < 0) x = 0;
        if(x > 100) x = 100;
        if(y < 0) y = 0;
        if(y > 100) y = 100;
    }
};
