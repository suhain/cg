
#include <gtest/gtest.h>
#include <cg/operations/orientation.h>
#include <cg/primitives/contour.h>
#include <misc/random_utils.h>
#include "random_utils.h"
#include <boost/random.hpp>

using namespace util;
using namespace cg;

TEST(orientation,
     uniform_line)
{
    uniform_random_real<double, boost::random::mt19937> distr(-(1LL << 53), (1LL << 53));
    std::vector<point_2>                  pts = uniform_points(1000);

    for (size_t l = 0, ln = 1; ln < pts.size(); l = ln++)
    {
        point_2 a = pts[l];
        point_2 b = pts[ln];

        for (size_t k = 0; k != 1000; ++k)
        {
            double      t = distr();
            point_2 c = a + t * (b - a);

            EXPECT_EQ(orientation(a, b, c), *orientation_r()(a, b, c));
        }
    }
}

TEST(orientation, contour_orientation)
{
   contour_2 contour1({{1, 1}, {2, 0}, {0, 1.1}});
   EXPECT_EQ(orientation(contour1), CG_CLOCKWISE);
   
   contour_2 contour2({{1, 1}, {0, 1.1}, {2, 0}});
   EXPECT_EQ(orientation(contour2), CG_COUNTERCLOCKWISE);
   
   contour_2 contour3({{0, 0}, {-1, 2}, {2, 3}, {3, 4}, {1, -1}});
   EXPECT_EQ(orientation(contour3), CG_CLOCKWISE);
   
   contour_2 contour4({{1, -1}, {3, 4}, {2, 3}, {-1, 2}, {0, 0}});
   EXPECT_EQ(orientation(contour4), CG_COUNTERCLOCKWISE);
}
