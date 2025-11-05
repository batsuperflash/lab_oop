#include "gtest/gtest.h"
#include "point.hpp"
#include "triangle.hpp"
#include "array.hpp"
#include <memory>

TEST(PointTest, DistanceAndEquality) {
    Point<int> a{0,0}, b{3,4};
    EXPECT_EQ(a.distance_to(b), 5);
    Point<int> c{0,0};
    EXPECT_TRUE(a == c);
}

TEST(TriangleTest, AreaAndCentroid) {
    Triangle<double> t(Point<double>{0,0}, Point<double>{4,0}, Point<double>{0,3});
    EXPECT_DOUBLE_EQ(t.area(), 6.0);
    Point<double> centroid = t.centroid();
    EXPECT_DOUBLE_EQ(centroid.x, 4.0/3);
    EXPECT_DOUBLE_EQ(centroid.y, 1.0);
}

TEST(ArrayTest, PushAndRemove) {
    Array<std::shared_ptr<Figure<double>>> arr;
    arr.push_back(std::make_shared<Triangle<double>>(Point<double>{0,0}, Point<double>{1,0}, Point<double>{0,1}));
    arr.push_back(std::make_shared<Triangle<double>>(Point<double>{0,0}, Point<double>{2,0}, Point<double>{0,2}));
    EXPECT_EQ(arr.size(),2);
    double total = arr.total_area();
    EXPECT_GT(total,0);
    arr.remove_at(0);
    EXPECT_EQ(arr.size(),1);
}
