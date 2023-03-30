#include <iostream>
#include "Utilities.h"

Number square(Number n)     { return n * n; }
Number abs(Number n)        { return (n < Number("0")) ? (Number("-1") * n) : n; }
Number sign(Number n)       { return (n < Number("0")) ? Number("-1") : Number("1"); }
Number distSquared(SimplePoint2D a, SimplePoint2D b)
{
    return square(a.x - b.x) + square(a.y - b.y);
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

void printSimplePoint2D(SimplePoint2D sp)
{
    std::cout << "(" << sp.x << " " << sp.y << ")";
}
void printSegment2D(Segment2D s)
{
    std::cout << "(segment ";
    printSimplePoint2D(s.leftEndPoint);
    std::cout << " ";
    printSimplePoint2D(s.rightEndPoint);
    std::cout << ")" << std::endl;
}
void printRegion2D(Region2D r)
{
    for (Segment2D s : r)
        printSegment2D(s);
}

// Returns True if these three points make a counter-clockwise turn, False if clockwise or colinear.
bool isCounterClockwiseTurn(SimplePoint2D p1, SimplePoint2D p2, SimplePoint2D p3)
{
    Number v1_x = p2.x - p1.x;
    Number v1_y = p2.y - p1.y;
    Number v2_x = p3.x - p2.x;
    Number v2_y = p3.y - p2.y;

    Number cross_product_z = (v1_x * v2_y) - (v1_y * v2_x);
    return cross_product_z > ZERO;
}
