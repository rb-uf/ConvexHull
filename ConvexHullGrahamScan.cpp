
#include <vector>
#include <algorithm>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Segment2D.h"


SimplePoint2D origin = SimplePoint2D(0, 0);

Number square(Number n)     { return n * n; }
Number abs(Number n)        { return (n < 0) ? (Number("-1") * n) : n; }
Number sign(Number n)       { return (n < 0) ? Number("-1") : Number("1"); }

Number distSquared(SimplePoint2D a, SimplePoint2D b)
{
    return square(a.x - b.x) + square(a.y - b.y);
}
Number angleFactor(SimplePoint2D sp)
{
    return sign(sp.x) * (square(sp.x) / (square(sp.x) + square(sp.y)));
}
SimplePoint2D relativeCoord(SimplePoint2D origin, SimplePoint2D p)
{
    return SimplePoint2D(p.x - origin.x, p.y - origin.y);
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
        return distSquared(origin, p1) > distSquared(origin, p2);
}

// Returns True if these three points make a counter-clockwise turn, False if clockwise or colinear.
bool isCounterClockwiseTurn(SimplePoint2D p1, SimplePoint2D p2, SimplePoint2D p3)
{
    Number v1_x = p2.x - p1.x;
    Number v1_y = p2.y - p1.y;
    Number v2_x = p3.x - p2.x;
    Number v2_y = p3.y - p2.y;

    Number cross_product_z = (v1_x * v2_y) - (v1_y * v2_x);
    return cross_product_z > 0;
}

// Converts an vector of SimplePoint2D into a vector of Segment2Ds.
// Segments connect one point to the next, according to the ordering of the points.
// If the first and last point are not equal, a segment will be drawn between them as well.
std::vector<Segment2D> pointsToSegments(std::vector<SimplePoint2D> points)
{
    std::vector<Segment2D> segments;

    for (int i = 0; i < points.size()-1; i++)
        segments.push_back(Segment2D(points[i], points[i+1]));

    if (points.front() != points.back())
        segments.push_back(Segment2D(points.front(), points.back()));

    return segments;
}


// https://en.wikipedia.org/wiki/Graham_scan
std::vector<Segment2D> ConvexHullGrahamScan(std::vector<SimplePoint2D> points)
{
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
        while (stack.size() > 1 && isCounterClockwiseTurn(stack[stack.size()-2], stack.back(), p) <= 0)
            stack.pop_back();
        stack.push_back(p);
    }

    return pointsToSegments(stack);
}

