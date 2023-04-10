#include <vector>
#include <algorithm>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Segment2D.h"
#include "Point2D.h"
#include "Region2D.h"
#include "Utilities.h"

// Returns between 1 and -1 (inclusive) for the polar angle of the point.
// sp must not be the origin.
Number angleFactor(const SimplePoint2D& sp)
{
    Number x_sq = sp.x.square();
    return sp.x.sign() * (x_sq / (x_sq + sp.y.square()));
}

// https://en.wikipedia.org/wiki/Graham_scan
Region2D ConvexHullGrahamScan(const Point2D& p2D)
{
    if (p2D.count() < 3)
        return Region2D();

    std::vector<SimplePoint2D> points = Point2DToVector(p2D);

    /* Let p0 be the point with the lowest y-coord and lowest x-coord (in that order) */
    SimplePoint2D p0 = points[0];
    for (SimplePoint2D p : points)
        if ((p.y < p0.y) || (p.y == p0.y && p.x < p0.x))
            p0 = p;

    /* A lambda function that compares the angles of p1 and p2 relative to p0. */
    SimplePoint2D origin = SimplePoint2D(Number("0"), Number("0"));
    auto comp = [&p0, &origin](SimplePoint2D p1, SimplePoint2D p2) {
        if (p0 == p2)
            return false;
        if (p0 == p1)
            return true;

        Number a1 = angleFactor(relativeCoord(p0, p1));
        Number a2 = angleFactor(relativeCoord(p0, p2));

        if (a1 != a2)
            return a1 > a2;
        else
            return distSquared(origin, p1) < distSquared(origin, p2);
    };

    // Sort points by polar angle with p0
    std::sort(points.begin(), points.end(), comp);

    std::vector<SimplePoint2D> stack;
    for (SimplePoint2D p : points) {
        while (stack.size() > 1 && isCounterClockwiseTurn(stack[stack.size()-2], stack.back(), p) <= 0) {
            stack.pop_back();
        }
        stack.push_back(p);
    }

    return Region2D(pointsToSegments(stack));
}

