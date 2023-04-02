#include <iostream>
#include "Utilities.h"

Number distSquared(SimplePoint2D a, SimplePoint2D b)
{
    return (a.x - b.x).square() + (a.y - b.y).square();
}

SimplePoint2D relativeCoord(SimplePoint2D origin, SimplePoint2D p)
{
    return SimplePoint2D(p.x - origin.x, p.y - origin.y);
}
std::vector<SimplePoint2D> Point2DToVector(Point2D Point2D_points)
{
    std::vector<SimplePoint2D> points;
    for (SimplePoint2D p : Point2D_points)
        points.push_back(p);
    return points;
}

// Returns True if these three points make a counter-clockwise turn, False if clockwise or colinear.
bool isCounterClockwiseTurn(SimplePoint2D p1, SimplePoint2D p2, SimplePoint2D p3)
{
    Number v1_x = p2.x - p1.x;
    Number v1_y = p2.y - p1.y;
    Number v2_x = p3.x - p2.x;
    Number v2_y = p3.y - p2.y;

    Number cross_product_z = (v1_x * v2_y) - (v1_y * v2_x);
    return cross_product_z > Number("0");
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
