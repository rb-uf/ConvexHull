#include <vector>
#include <algorithm>
#include <iostream>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Segment2D.h"
#include "Region2D.h"
#include "Point2D.h"
#include "Utilities.h"

// returns 2 for the origin, and between 1 and -1 (inclusive) for all others.
Number angleFactor(SimplePoint2D sp)
{
    if (sp.x == ZERO && sp.y == ZERO)
        return Number("2");     // the origin is always first
    return sign(sp.x) * (square(sp.x) / (square(sp.x) + square(sp.y)));
}

// In an angular sweep counter-clockwise from the positive x axis to the negative
// x axis, if p1 is encountered before p2, return true. Otherwise, false.
// Calculated relative to an origin at (0, 0).
bool angularCompareFunc(SimplePoint2D p1, SimplePoint2D p2)
{
    // Note: p1 and p2 can be treated as position vectors
    // Inspiration: https://en.wikipedia.org/wiki/Cosine_similarity

    Number a1 = angleFactor(p1);
    Number a2 = angleFactor(p2);

    if (a1 != a2)
        return a1 > a2;
    else
        return distSquared(ORIGIN, p1) > distSquared(ORIGIN, p2);
}

// https://en.wikipedia.org/wiki/Graham_scan
Region2D ConvexHullGrahamScan(Point2D Point2D_points)
{
    std::vector<SimplePoint2D> points = Point2DToVector(Point2D_points);

    if (points.size() <= 3)
        return pointsToSegments(points);

    // Let p0 be the point with the lowest y-coord and lowest x-coord (in that order)
    SimplePoint2D p0 = points[0];
    for (SimplePoint2D p : points) {
        if ((p.y < p0.y) || (p.y == p0.y && p.x < p0.x))
            p0 = p;
    }

    // This is a lambda expression. It will be used by std::sort to order the points.
    // A lambda function is needed here because the ordering is dependent on p0.
    auto comp = [p0](SimplePoint2D p1, SimplePoint2D p2) {
        return angularCompareFunc(relativeCoord(p0, p1), relativeCoord(p0, p2));
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

