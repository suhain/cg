#include <gtest/gtest.h>
#include <cg/operations/contains/segment_point.h>
#include <cg/operations/contains/triangle_point.h>
#include <cg/operations/contains/convex_contour_point.h>
#include <cg/operations/contains/contour_point.h>

TEST(contains,
        triangle_point)
{
    using cg::point_2;

    cg::triangle_2 t(point_2(0, 0), point_2(1, 1), point_2(2, 0));

    for (size_t l = 0; l != 3; ++l)
    {
        EXPECT_TRUE(cg::contains(t, t[l]));
    }

    EXPECT_TRUE(cg::contains(t, point_2(1, 0.5)));
    EXPECT_TRUE(cg::contains(t, point_2(1, 0)));
    EXPECT_TRUE(cg::contains(t, point_2(0.5, 0.5)));
    EXPECT_TRUE(cg::contains(t, point_2(1.5, 0.5)));
    EXPECT_FALSE(cg::contains(t, point_2(0, 1)));
    EXPECT_FALSE(cg::contains(t, point_2(2, 1)));
    EXPECT_FALSE(cg::contains(t, point_2(1, -1)));
}

TEST(contains,
        segment_point)
{
    using cg::point_2;

    cg::segment_2 s(point_2(0, 0), point_2(2, 2));

    for (size_t l = 0; l != 2; ++l)
    {
        EXPECT_TRUE(cg::contains(s, s[l]));
    }

    EXPECT_TRUE(cg::contains(s, point_2(1, 1)));
    EXPECT_FALSE(cg::contains(s, point_2(-1, -1)));
    EXPECT_FALSE(cg::contains(s, point_2(4, 4)));
    EXPECT_FALSE(cg::contains(s, point_2(1, 0)));
    EXPECT_FALSE(cg::contains(s, point_2(0, 1)));
}

TEST(contain, point_to_convex_contour)
{
    cg::contour_2 contour1({
        {0, 0},
        {2, 2},
        {4, 0}
    });
    cg::point_2 a1(2, 1);
    EXPECT_TRUE(cg::contains_convex(a1, contour1));
    cg::point_2 a2(1, 1);
    EXPECT_TRUE(cg::contains_convex(a2, contour1));

    cg::contour_2 contour3({
        {0, 0},
        {-1, 2},
        {2, 3},
        {2, 1},
        {1, -1}
    });
    cg::point_2 a3(1, 1);
    EXPECT_TRUE(cg::contains_convex(a3, contour3));

    cg::contour_2 contour4({
        {0, 0},
        {2, -1},
        {2, -3},
        {0, -1},
        {-2, -3},
        {-2, -1}
    });
    cg::point_2 a4(0, -1);
    EXPECT_TRUE(cg::contains_convex(a4, contour4));

    cg::point_2 a5(0.9, -2);
    EXPECT_FALSE(cg::contains_convex(a5, contour4));

    cg::point_2 a6(2.001, -2);
    EXPECT_FALSE(cg::contains_convex(a6, contour4));
}

TEST(contain, point_to_nonconvex_contour)
{
    cg::contour_2 contour1({
        {0, 0},
        {2, 2},
        {4, 0}});
    cg::point_2 a1(2, 1);
    EXPECT_TRUE(cg::contains(a1, contour1));
    cg::point_2 a2(1, 1);
    EXPECT_TRUE(cg::contains(a2, contour1));

    cg::contour_2 contour2({
        {0, 0},
        {-1, 2},
        {2, 3},
        {2, 1},
        {1, -1}});
    EXPECT_TRUE(cg::contains(a2, contour2));

    cg::contour_2 contour3({
        {0, 0},
        {2, -1},
        {2, -3},
        {0, -1},
        {-2, -3},
        {-2, -1}});
    cg::point_2 a3(0, -2);
    EXPECT_FALSE(cg::contains(a3, contour3));
    cg::point_2 a4(0.9, -2);
    EXPECT_FALSE(cg::contains(a4, contour3));
    cg::point_2 a5(2.001, -2);
    EXPECT_FALSE(cg::contains(a5, contour3));

    cg::contour_2 contour4({
        {0, 0},
        {4, 0},
        {2, -4},
        {2, -2},
        {0, -4}});
    cg::point_2 a6(-1, -1);
    EXPECT_FALSE(cg::contains(a6, contour4));
    cg::point_2 a7(1, -4);
    EXPECT_FALSE(cg::contains(a7, contour4));
    cg::point_2 a8(1, -2);
    EXPECT_TRUE(cg::contains(a8, contour4));
}
