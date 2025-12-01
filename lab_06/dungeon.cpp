#include "dungeon.h"
#include <cstdlib>
#include <ctime>

// ---------------- Observer ----------------
void ConsoleObserver::onKill(const std::string& killer, const std::string& victim) {
    std::cout << killer << " killed " << victim << "\n";
}

void FileObserver::onKill(const std::string& killer, const std::string& victim) {
    std::ofstream out("log.txt", std::ios::app);
    out << killer << " killed " << victim << "\n";
}

// ---------------- BattleVisitor ----------------
void BattleVisitor::addObserver(Observer* o) { observers.push_back(o);}
void BattleVisitor::notify(const std::string& k, const std::string& v) {
    for(auto* o: observers) o->onKill(k,v);
}

bool BattleVisitor::visit(Dragon& a, NPC& b) {
    if(b.getType()=="Knight" || b.getType()=="Frog") {
        notify(b.getName(), a.getName());
        return false;
    }
    return false;
}
bool BattleVisitor::visit(Knight& a, NPC& b) {
    if(b.getType()=="Dragon") {
        notify(a.getName(), b.getName());
        return true;
    }
    if(b.getType()=="Frog") {
        notify(b.getName(), a.getName());
        return false;
    }
    return false;
}
bool BattleVisitor::visit(Frog& a, NPC& b) {
    notify(a.getName(), b.getName());
    return true;
}

// ---------------- NPC acceptFight ----------------
bool Dragon::acceptFight(Visitor& v, NPC& other){ return v.visit(*this,other);}
bool Knight::acceptFight(Visitor& v, NPC& other){ return v.visit(*this,other);}
bool Frog::acceptFight(Visitor& v, NPC& other){ return v.visit(*this,other);}

// ---------------- Factory ----------------
std::shared_ptr<NPC> NPCFactory::create(const std::string& type, const std::string& name, double x, double y){
    if(type=="Dragon") return std::make_shared<Dragon>(name,x,y);
    if(type=="Knight") return std::make_shared<Knight>(name,x,y);
    if(type=="Frog") return std::make_shared<Frog>(name,x,y);
    return nullptr;
}

// ---------------- Dungeon ----------------
void Dungeon::addNPC(std::shared_ptr<NPC> npc){
    if(names.count(npc->getName())==0){
        npcs.push_back(npc);
        names.insert(npc->getName());
    }
}

void Dungeon::print(){
    for(auto& n: npcs)
        std::cout << n->getType()<<" "<<n->getName()<<" ("<<n->getX()<<","<<n->getY()<<")\n";
}

void Dungeon::save(const std::string& file){
    std::ofstream out(file);
    for(auto& n: npcs)
        out<<n->getType()<<" "<<n->getName()<<" "<<n->getX()<<" "<<n->getY()<<"\n";
}

void Dungeon::load(const std::string& file){
    npcs.clear();
    names.clear();
    std::ifstream in(file);
    std::string type,name;
    double x,y;
    while(in>>type>>name>>x>>y)
        addNPC(NPCFactory::create(type,name,x,y));
}

void Dungeon::battle(double range){
    BattleVisitor visitor;
    ConsoleObserver c; FileObserver f;
    visitor.addObserver(&c);
    visitor.addObserver(&f);

    std::vector<std::shared_ptr<NPC>> alive = npcs;

    for(size_t i=0;i<alive.size();i++){
        for(size_t j=i+1;j<alive.size();j++){
            if(alive[i] && alive[j] && alive[i]->distanceTo(*alive[j])<=range){
                bool res1 = alive[i]->acceptFight(visitor,*alive[j]);
                bool res2 = alive[j]->acceptFight(visitor,*alive[i]);
                if(!res1) alive[i]=nullptr;
                if(!res2) alive[j]=nullptr;
            }
        }
    }

    npcs.clear();
    names.clear();
    for(auto& a: alive)
        if(a){ npcs.push_back(a); names.insert(a->getName());}
}

// ---------------- Тестовые методы ----------------
size_t Dungeon::getNPCCount() const { return npcs.size(); }
std::vector<std::shared_ptr<NPC>> Dungeon::getNPCList() const { return npcs; }
