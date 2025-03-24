#include <gtest/gtest.h>
#include "donut.h"

// lecture activity create a test for the topping setter, and drizzle setter

TEST(donutTest, constructorAndGetterTest)
{
    EXPECT_NO_THROW(Donut d("Chocolate", "Peanuts", "Peanut Butter"));
    EXPECT_NO_THROW(Donut d2("chocolate", "peanuts", "peanut butter"));
    Donut d("Chocolate", "Peanuts", "Peanut Butter");
    EXPECT_EQ(d.getIcing(), Donut::CHOCOLATEICING);
    EXPECT_EQ(d.getTopping(), Donut::PEANUTS);
    EXPECT_EQ(d.getDrizzle(), Donut::PEANUTBUTTER);
    EXPECT_ANY_THROW(Donut d("coco", "nut", "stuff"));
}

TEST(donutTest, icingSetterTest)
{
    Donut d("Chocolate", "Peanuts", "Peanut Butter");
    EXPECT_ANY_THROW(d.setIcing("coco"));
    EXPECT_NO_THROW(d.setIcing("MAplE"));
    EXPECT_EQ(d.getIcing(), Donut::MAPLE);
}

extern "C" int startTest(int x, char **y)
{
    testing::InitGoogleTest(&x, y);
    int code = RUN_ALL_TESTS();
    return code;
}
extern "C" int __wrap_main(int x, char **y)
{
    return startTest(x, y);
}  

TEST(donutTest, toppingSetterTest)
{
    Donut d("Chocolate", "Peanuts", "Peanut Butter");
    EXPECT_ANY_THROW(d.setTopping("Vanilla"));
    EXPECT_NO_THROW(d.setTopping("OrEo"));
    EXPECT_EQ(d.getTopping(), Donut::OREO);
}
TEST(donutTest, drizzleSetterTest)
{
    Donut d("Chocolate", "Peanuts", "Peanut Butter");
    EXPECT_ANY_THROW(d.setDrizzle("Bacon"));
    EXPECT_NO_THROW(d.setDrizzle("CaRamel"));
    EXPECT_EQ(d.getDrizzle(), Donut::CARAMEL);
}

