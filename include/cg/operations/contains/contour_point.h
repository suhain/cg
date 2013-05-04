#pragma once

#include "cg/primitives/point.h"
#include "cg/primitives/segment.h"
#include "cg/primitives/contour.h"
#include "cg/operations/orientation.h"
#include "cg/operations/has_intersection/segment_segment.h"
#include "cg/operations/contains/segment_point.h"

#include <boost/random.hpp>

namespace cg
{

    inline bool contains_random_point(const point_2 &p, const contour_2 &cont)
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

    inline bool contains_trace(const point_2 &p, const contour_2 &cont)
    {
        auto it = std::max_element(cont.begin(), cont.end());
        segment_2 line(p, point_2(it->x * 2, it->y));
        int count = 0;
        double height = 0;
        auto circ = cont.circulator(cont.begin());

        for (size_t i = 0; i != cont.vertices_num(); i++)
        {
            auto curr = circ++;
            auto next = circ;
            segment_2 side(*curr, *next);
            if (contains(side, p)) return true;
            orientation_t t1 = orientation(*curr, line[0], line[1]);
            orientation_t t2 = orientation(*next, line[0], line[1]);
            if (t1 == 0 || t2 == 0)
            {
                if (t1 == 0 && t2 == 0) continue;
                if (t1 == 0)
                {
                    ++count;
                    height = curr->y;
                }
                else 
                {
                    if ((height > curr->y && next->y > curr->y) || (height < curr->y && next->y < curr->y)) ++count;
                }
            }
            else if (has_intersection(line, side)) ++count;
        }
        return count & 1;
    }
    
    inline bool contains(const point_2 &p, const contour_2 &cont)
    {
        //return contains_random_point(p, cont);
        return contains_trace(p, cont);
    }
}