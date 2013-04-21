#pragma once 

#include "graham.h"
#include <boost/utility.hpp>
#include <algorithm>

namespace cg
{

    template<class BidIter>
    BidIter contour_andrew_hull(BidIter p, BidIter q)
    {
        return contour_graham_hull(p, q);
    }

    template<class BidIter>
    BidIter andrew_hull(BidIter p, BidIter q)
    {
        if (p == q)
            return p;
        BidIter t = ++p;
        p--;
        if (t == q)
            return q;
        std::iter_swap(p, std::min_element(p, q));
        std::iter_swap(t, std::max_element(p, q));
        t++;
        BidIter n = boost::next(p);
        BidIter bound = std::partition(t, q, [&p, &n] (point_2 const& a)
        {
            return orientation(a, *p, *n) != CG_LEFT;
        });
        p++;
        std::sort(p, bound, std::less<point_2>());
        std::sort(bound, q, std::greater<point_2>());
        return contour_andrew_hull(p, q);
    }
}