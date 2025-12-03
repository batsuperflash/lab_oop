#include "dungeon.h"
#include <cstdlib>
#include <cmath>
#include <chrono>
#include <thread>

std::shared_ptr<NPC> NPCFactory::create(const std::string& type,
                                        const std::string& name,
                                        double x, double y) {
    if(type=="Dragon") return std::make_shared<Dragon>(name,x,y);
    if(type=="Knight") return std::make_shared<Knight>(name,x,y);
    if(type=="Frog") return std::make_shared<Frog>(name,x,y);
    return nullptr;
}

void Dungeon::addNPC(std::shared_ptr<NPC> npc){
    std::unique_lock lock(npc_mutex);
    if(names.count(npc->getName())==0){
        npcs.push_back(npc);
        names.insert(npc->getName());
    }
}

size_t Dungeon::getNPCCount() {
    std::shared_lock lock(npc_mutex);
    return npcs.size();
}

std::vector<std::shared_ptr<NPC>> Dungeon::getNPCList() {
    std::shared_lock lock(npc_mutex);
    return npcs;
}

// ---------------- Поток перемещения ----------------
void Dungeon::moveAllNPCs() {
    while(!stop) {
        {
            std::unique_lock lock(npc_mutex);
            for(auto& n : npcs) {
                if(n->isAlive()) {
                    double dx = (rand()%3 - 1); // -1,0,1
                    double dy = (rand()%3 - 1);
                    n->move(dx, dy);

                    // проверка расстояния для боя
                    for(auto& m : npcs) {
                        if(n!=m && m->isAlive() && n->distanceTo(*m)<=5) {
                            {
                                std::lock_guard<std::mutex> qlock(fight_mutex);
                                fight_queue.push({n,m});
                            }
                            fight_cv.notify_one();
                        }
                    }
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
}

// ---------------- Поток боёв ----------------
void Dungeon::battleThread() {
    while(!stop) {
        std::pair<std::shared_ptr<NPC>, std::shared_ptr<NPC>> fight;
        {
            std::unique_lock<std::mutex> qlock(fight_mutex);
            fight_cv.wait_for(qlock, std::chrono::milliseconds(100), [&]{ return !fight_queue.empty() || stop; });
            if(fight_queue.empty()) continue;
            fight = fight_queue.front();
            fight_queue.pop();
        }

        auto& a = fight.first;
        auto& b = fight.second;
        if(!a->isAlive() || !b->isAlive()) continue;

        int atk = a->attack();
        int defb = b->defense();
        int atk2 = b->attack();
        int defa = a->defense();

        if(atk>defb) a->kill();
        if(atk2>defa) b->kill();
    }
}

// ---------------- Поток вывода ----------------
void Dungeon::printMap() {
    while(!stop) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::shared_lock lock(npc_mutex);
        std::lock_guard<std::mutex> cout_lock(cout_mutex);
        std::cout << "---- Map ----\n";
        for(auto& n : npcs) {
            if(n->isAlive())
                std::cout << n->getType() << " " << n->getName()
                          << " (" << n->getX() << "," << n->getY() << ")\n";
        }
        std::cout << "------------\n";
    }
}
