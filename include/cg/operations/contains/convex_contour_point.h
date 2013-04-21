#pragma once

#include "cg/primitives/point.h"
#include "cg/primitives/contour.h"
#include "cg/operations/contains/triangle_point.h"
#include "cg/operations/orientation.h"
#include <algorithm>

namespace cg
{

    inline bool contains_convex(point_2 const& p, contour_2 const& cont)
    {
        if (contains(triangle_2(*cont.begin(), *(cont.begin() + 1), *(cont.end() - 1)), p)) return true;
        auto it = std::lower_bound(cont.begin(), cont.end(), p,
                [&](point_2 const& a, point_2 const& b)
                {
                    return orientation(cont[0], a, b) == CG_RIGHT;
                });
        auto x = it;
        x--;
        return contains(triangle_2(cont[0], *it, *x), p);
    }
}

