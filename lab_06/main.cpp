#include "dungeon.h"
#include <cstdlib>
#include <ctime>

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
double randomCoord() { return rand()%501; }

int main(int argc, char* argv[]){
    if(argc<3){ std::cout << "Usage: ./dungeon <num_npc> <battle_range>\n"; return 1;}
    int num_npc = atoi(argv[1]);
    double range = atof(argv[2]);

    Dungeon d;
    srand(time(nullptr));
    for(int i=0;i<num_npc;i++)
        d.addNPC(NPCFactory::create(randomType(),randomName(),randomCoord(),randomCoord()));

    std::cout<<"Initial NPCs:\n";
    d.print();
    std::cout<<"\nStarting battle with range="<<range<<"\n";
    d.battle(range);
    std::cout<<"\nAfter battle:\n";
    d.print();
    d.save("output.txt");
    std::cout<<"\nSaved NPCs to output.txt\n";
}
