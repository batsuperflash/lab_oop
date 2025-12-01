#include <gtest/gtest.h>
#include "../dungeon.h"

TEST(NPCTest, UniqueNames){
    Dungeon d;
    auto n1 = NPCFactory::create("Dragon","A",100,100);
    auto n2 = NPCFactory::create("Knight","A",200,200);
    d.addNPC(n1);
    d.addNPC(n2);
    EXPECT_EQ(d.getNPCCount(),1);
}

TEST(BattleTest, DragonVsKnight){
    Dungeon d;
    d.addNPC(NPCFactory::create("Dragon","Drako",100,100));
    d.addNPC(NPCFactory::create("Knight","Lancelot",105,105));
    d.battle(10);
    auto s = d.getNPCList();
    ASSERT_EQ(s.size(),1);
    EXPECT_EQ(s[0]->getType(),"Knight");
}

TEST(BattleTest, FrogKillsAll){
    Dungeon d;
    d.addNPC(NPCFactory::create("Frog","Gromp",50,50));
    d.addNPC(NPCFactory::create("Dragon","Drako",52,52));
    d.addNPC(NPCFactory::create("Knight","Lancelot",54,54));
    d.battle(10);
    auto s = d.getNPCList();
    ASSERT_EQ(s.size(),1);
    EXPECT_EQ(s[0]->getType(),"Frog");
}

TEST(FactoryTest, CreateNPC){
    auto n = NPCFactory::create("Dragon","Draco",100,100);
    ASSERT_NE(n,nullptr);
    EXPECT_EQ(n->getType(),"Dragon");
}

TEST(SaveLoadTest, SaveAndLoad){
    Dungeon d;
    d.addNPC(NPCFactory::create("Dragon","D1",10,10));
    d.addNPC(NPCFactory::create("Knight","K1",20,20));
    d.save("test_output.txt");

    Dungeon d2;
    d2.load("test_output.txt");
    EXPECT_EQ(d2.getNPCCount(),2);
}
