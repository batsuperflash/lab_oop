#include "dungeon.h"
#include <thread>
#include <cstdlib>
#include <ctime>
#include <iostream>

std::string randomName() {
    static int counter = 1;
    return "NPC" + std::to_string(counter++);
}

std::string randomType() {
    int t = rand()%3;
    if(t==0) return "Dragon";
    if(t==1) return "Knight";
    return "Frog";
}

int main() {
    srand(time(nullptr));
    Dungeon d;

    // создаём 50 NPC
    for(int i=0;i<50;i++)
        d.addNPC(NPCFactory::create(randomType(), randomName(),
                                    rand()%101, rand()%101));

    // потоки
    std::thread move_thread([&]{ d.moveAllNPCs(); });
    std::thread battle_thread([&]{ d.battleThread(); });
    std::thread print_thread([&]{ d.printMap(); });

    // ждём 30 секунд
    std::this_thread::sleep_for(std::chrono::seconds(30));
    d.stopThreads();

    move_thread.join();
    battle_thread.join();
    print_thread.join();

    // вывод выживших
    std::cout << "---- Survivors ----\n";
    auto alive = d.getNPCList();
    for(auto& n : alive) {
        if(n->isAlive())
            std::cout << n->getType() << " " << n->getName()
                      << " (" << n->getX() << "," << n->getY() << ")\n";
    }
}
