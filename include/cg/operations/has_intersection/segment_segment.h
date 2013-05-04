#pragma once

#include <cg/primitives/segment.h>
#include <cg/primitives/point.h>
#include <cg/operations/orientation.h>
#include <cg/operations/contains/segment_point.h>
#include <boost/optional.hpp>

namespace cg
{
    template<class Scalar>
    bool has_intersection(segment_2t<Scalar> const &a,
                          segment_2t<Scalar> const &b)
    {
        orientation_t ab[2];

        for (size_t l = 0; l != 2; ++l)
        {
            ab[l] = orientation(a[0], a[1], b[l]);
        }

        if ((ab[0] == ab[1]) && (ab[0] == CG_COLLINEAR))
        {
            return ((min(a) <= b[0]) && (max(a) >= b[0])) || ((min(a) <= b[1]) && (max(a) >= b[1]))
                   || ((min(b) <= a[0]) && (max(b) >= a[0])) || ((min(b) <= a[1]) && (max(b) >= a[1]));
        }

        if (ab[0] == ab[1])
        {
            return false;
        }

        for (size_t l = 0; l != 2; ++l)
        {
            ab[l] = orientation(b[0], b[1], a[l]);
        }

        return ab[0] != ab[1];
    }
    
    inline boost::optional<point_2> intersection(segment_2 a, segment_2 b)
    {
        if (!has_intersection(a, b)) 
            return boost::none;
        if (a[1].y == a[0].y) {
            swap(a, b);
        }
        double A1 = a[1].y - a[0].y;
        double B1 = a[0].x - a[1].x;
        double C1 = a[0].y * a[1].x - a[0].x * a[1].y;
        
        double A2 = b[1].y - b[0].y;
        double B2 = b[0].x - b[1].x;
        double C2 = b[0].y * b[1].x - b[0].x * b[1].y;
        
        double k = A1 / A2;
        double y = (-C1 + k * C2) / (B1 - k * B2);
        double x = (-B1 * y - C1) / A1;
        return point_2(x, y);
    }
}
