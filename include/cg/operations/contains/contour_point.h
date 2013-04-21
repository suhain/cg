#pragma once

#include "cg/primitives/point.h"
#include "cg/primitives/contour.h"
#include "cg/operations/orientation.h"
#include "cg/operations/has_intersection/segment_segment.h"
#include "cg/operations/contains/segment_point.h"

#include <boost/random.hpp>

namespace cg
{

    inline bool contains(const point_2 &p, const contour_2 &cont)
    {
        boost::random::mt19937 gen;
        boost::random::uniform_real_distribution<> distr;
        int count = 0;
        auto circ = cont.circulator(cont.begin());
        double m = (1LL << 25 - 1) * 1.0;
        segment_2 segment(p, point_2(distr(gen) * m, distr(gen) * m));

        for (size_t i = 0; i != cont.vertices_num(); i++)
        {
            auto curr = *circ++;
            auto next = *circ;
            if (p == curr || p == next) return true;
            segment_2 side(curr, next);
            if (contains(side, p)) return true;
            if (has_intersection(side, segment)) count++;
            curr = next;
        }
        return count & 1;
    }
}