#include "gtest/gtest.h"
#include "../dungeon.h"
#include "../NPCtypes.h"
#include <memory>

TEST(DungeonTest, AddNPC) {
    Dungeon d;

    auto npc1 = NPCFactory::create("Dragon", "D1", 10, 10);
    auto npc2 = NPCFactory::create("Knight", "K1", 20, 20);

    d.addNPC(npc1);
    d.addNPC(npc2);

    EXPECT_EQ(d.getNPCCount(), 2);
    auto list = d.getNPCList();
    EXPECT_EQ(list[0]->getName(), "D1");
    EXPECT_EQ(list[1]->getName(), "K1");
}

// Добавляем свой main, чтобы линковка прошла на Mac
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
