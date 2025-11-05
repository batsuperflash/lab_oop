// #include <gtest/gtest.h>
// #include "../Rectangle.h"
// #include "../Trapezoid.h"
// #include "../Rhombus.h"

// // тест прямоугольника
// TEST(RectangleTest, AreaAndCenter) {
//     Rectangle r(4, 2);
//     EXPECT_EQ(r.area(), 8);
//     Point c = r.center();
//     EXPECT_DOUBLE_EQ(c.x, 2);
//     EXPECT_DOUBLE_EQ(c.y, 1);
// }

// // тест трапеции
// TEST(TrapezoidTest, AreaAndCenter) {
//     Trapezoid t(2, 4, 3);
//     EXPECT_EQ(t.area(), 9);
//     Point c = t.center();
//     EXPECT_DOUBLE_EQ(c.x, 1);
//     EXPECT_DOUBLE_EQ(c.y, 1.5);
// }

// // тест ромба
// TEST(RhombusTest, AreaAndCenter) {
//     Rhombus rh(4, 6);
//     EXPECT_EQ(rh.area(), 12);
//     Point c = rh.center();
//     EXPECT_DOUBLE_EQ(c.x, 2);
//     EXPECT_DOUBLE_EQ(c.y, 3);
// }

// // тест оператора ==
// TEST(FigureEquality, Rectangle) {
//     Rectangle r1(3,5), r2(3,5);
//     EXPECT_TRUE(r1 == r2);
// }

// TEST(FigureEquality, Trapezoid) {
//     Trapezoid t1(1,2,3), t2(1,2,3);
//     EXPECT_TRUE(t1 == t2);
// }

// TEST(FigureEquality, Rhombus) {
//     Rhombus rh1(5,7), rh2(5,7);
//     EXPECT_TRUE(rh1 == rh2);
// }



#include <gtest/gtest.h>
#include "../Rectangle.h"
#include "../Trapezoid.h"
#include "../Rhombus.h"
#include <sstream>

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// тест прямоугольника: площадь и центр
TEST(RectangleTest, AreaAndCenter) {
    Rectangle r(4, 2);
    EXPECT_EQ(r.area(), 8);
    Point c = r.center();
    EXPECT_DOUBLE_EQ(c.x, 2);
    EXPECT_DOUBLE_EQ(c.y, 1);
}

// // тест трапеции: площадь и центр
// TEST(TrapezoidTest, AreaAndCenter) {
//     Trapezoid t(2, 4, 3);
//     EXPECT_EQ(t.area(), 9);
//     Point c = t.center();
//     EXPECT_DOUBLE_EQ(c.x, 1);
//     EXPECT_DOUBLE_EQ(c.y, 1.5);
// }

// тест ромба: площадь и центр
TEST(RhombusTest, AreaAndCenter) {
    Rhombus rh(4, 6);
    EXPECT_EQ(rh.area(), 12);
    Point c = rh.center();
    EXPECT_DOUBLE_EQ(c.x, 2);
    EXPECT_DOUBLE_EQ(c.y, 3);
}

// тест оператора ==
TEST(FigureEquality, Rectangle) {
    Rectangle r1(3,5), r2(3,5);
    EXPECT_TRUE(r1 == r2);
}

TEST(FigureEquality, Trapezoid) {
    Trapezoid t1(1,2,3), t2(1,2,3);
    EXPECT_TRUE(t1 == t2);
}

TEST(FigureEquality, Rhombus) {
    Rhombus rh1(5,7), rh2(5,7);
    EXPECT_TRUE(rh1 == rh2);
}

// тест копирования и перемещения
TEST(FigureCopyMove, Rectangle) {
    Rectangle r1(3,4);
    Rectangle r2 = r1;          // копирование
    EXPECT_TRUE(r1 == r2);

    Rectangle r3 = std::move(r1); // перемещение
    EXPECT_TRUE(r3 == r2);
}

// тест clone()
TEST(FigureClone, Trapezoid) {
    Trapezoid t1(2,3,4);
    Figure* t2 = t1.clone();
    EXPECT_TRUE(t1 == *t2);
    delete t2;
}

// // тест операторов ввода/вывода
// TEST(FigureIO, Rhombus) {
//     Rhombus r1(4,5);
//     std::stringstream ss;
//     ss << r1;
//     Rhombus r2;
//     ss >> r2;
//     EXPECT_TRUE(r1 == r2);
// }
