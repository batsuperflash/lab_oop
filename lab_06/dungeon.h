#pragma once
#include "NPC.h"
#include "NPCtypes.h"
#include <vector>
#include <memory>
#include <set>
#include <string>
#include <iostream>
#include <fstream>

// ---------------- Visitor ----------------
class Dragon;
class Knight;
class Frog;

class Visitor {
public:
    virtual bool visit(Dragon& a, NPC& b) = 0;
    virtual bool visit(Knight& a, NPC& b) = 0;
    virtual bool visit(Frog& a, NPC& b) = 0;
    virtual ~Visitor() = default;
};

// ---------------- Observer ----------------
class Observer {
public:
    virtual void onKill(const std::string& killer, const std::string& victim) = 0;
    virtual ~Observer() = default;
};

class ConsoleObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override;
};

class FileObserver : public Observer {
public:
    void onKill(const std::string& killer, const std::string& victim) override;
};

// ---------------- BattleVisitor ----------------
class BattleVisitor : public Visitor {
    std::vector<Observer*> observers;
public:
    void addObserver(Observer* o);
    void notify(const std::string& k, const std::string& v);
    bool visit(Dragon& a, NPC& b) override;
    bool visit(Knight& a, NPC& b) override;
    bool visit(Frog& a, NPC& b) override;
};

// ---------------- Factory ----------------
class NPCFactory {
public:
    static std::shared_ptr<NPC> create(const std::string& type,
                                       const std::string& name,
                                       double x, double y);
};

// ---------------- Dungeon ----------------
class Dungeon {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::set<std::string> names; // для уникальных имен
public:
    void addNPC(std::shared_ptr<NPC> npc);
    void print();
    void save(const std::string& file);
    void load(const std::string& file);
    void battle(double range);

    // Для тестов
    size_t getNPCCount() const;
    std::vector<std::shared_ptr<NPC>> getNPCList() const;
};
