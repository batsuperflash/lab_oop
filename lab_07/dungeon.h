#pragma once
#include "NPC.h"
#include "NPCtypes.h"
#include <vector>
#include <memory>
#include <set>
#include <string>
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <queue>
#include <condition_variable>
#include <thread>

class Visitor;

class NPCFactory {
public:
    static std::shared_ptr<NPC> create(const std::string& type,
                                       const std::string& name,
                                       double x, double y);
};

class Dungeon {
    std::vector<std::shared_ptr<NPC>> npcs;
    std::set<std::string> names;

public:
    std::shared_mutex npc_mutex;
    std::mutex cout_mutex;

    std::queue<std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>>> fight_queue;
    std::mutex fight_mutex;
    std::condition_variable fight_cv;

    void addNPC(std::shared_ptr<NPC> npc);
    void moveAllNPCs();
    void battleThread();
    void printMap();
    void stopThreads() { stop = true; }
    bool stop{false};

    size_t getNPCCount();
    std::vector<std::shared_ptr<NPC>> getNPCList();
};
