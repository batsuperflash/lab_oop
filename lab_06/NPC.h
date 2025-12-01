#ifndef NPC_H
#define NPC_H

#include <string>
#include <memory>
#include <cmath>

class Visitor;

class NPC {
protected:
    std::string name;
    double x{}, y{};

public:
    NPC(std::string n, double x, double y) : name(std::move(n)), x(x), y(y) {}
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    std::string getName() const { return name; }
    double getX() const { return x; }
    double getY() const { return y; }

    double distanceTo(const NPC& other) const {
        return std::sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
    }

    virtual bool acceptFight(Visitor& v, NPC& other) = 0;
};

#endif
