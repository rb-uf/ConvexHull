#include <vector>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Segment2D.h"
#include "Point2D.h"
#include "Region2D.h"
#include "Utilities.h"
#include <iostream>

/* https://en.wikipedia.org/wiki/Quickhull */

typedef std::vector<SimplePoint2D> vsp;
static Number zero = Number("0");

vsp mergeHulls(const vsp& hull_1, const SimplePoint2D& farPoint, const vsp& hull_2)
{
    vsp hull;
    hull.insert(hull.end(), hull_1.begin(), hull_1.end());
    hull.insert(hull.end(), farPoint);
    hull.insert(hull.end(), hull_2.begin(), hull_2.end());
    return hull;
}

/* https://en.wikipedia.org/wiki/Distance_from_a_point_to_a_line */
Number pointToLineDistSq(const SimplePoint2D& p,
                         const SimplePoint2D& l1,
                         const SimplePoint2D& l2)
{
    return ((l2.x - l1.x)*(l1.y - p.y) - (l1.x - p.x)*(l2.y - l1.y)).square()
           / distSquared(l1, l2);
}

SimplePoint2D
findFarthestPoint(const vsp& points,
                  const SimplePoint2D& line_p1,
                  const SimplePoint2D& line_p2)
{
    SimplePoint2D farPoint = points[0];
    Number maxDist = zero;
    for (SimplePoint2D p : points) {
        Number dist = pointToLineDistSq(p, line_p1, line_p2);
        if (dist > maxDist) {
            maxDist = dist;
            farPoint = p;
        }
    }
    return farPoint;
}

vsp getPointsOnOneSide(const vsp& points,
                       const SimplePoint2D& a,
                       const SimplePoint2D& b)
{
    vsp side;
    for (SimplePoint2D p : points)
        if (isCounterClockwiseTurn(a, b, p))
            side.push_back(p);
    return side;
}

vsp findHull(const vsp& _points,
             const SimplePoint2D& a,
             const SimplePoint2D& b)
{
    vsp points = getPointsOnOneSide(_points, a, b);
    if (points.size() == 0)
        return vsp();
    SimplePoint2D farPoint = findFarthestPoint(points, a, b);
    vsp h1 = findHull(points, a, farPoint);
    vsp h2 = findHull(points, farPoint, b);
    vsp h3 = mergeHulls(h1, farPoint,
                      h2);
    return h3;
}

Region2D ConvexHullQuickhull(const Point2D& p2D)
{
    if (p2D.count() < 3)
        return Region2D();

    vsp points = Point2DToVector(p2D);

    SimplePoint2D minPoint = points.front();
    SimplePoint2D maxPoint = points.back();
    for (SimplePoint2D p : points) {
        if (p < minPoint)
            minPoint = p;
        if (p > maxPoint)
            maxPoint = p;
    }

    vsp h3 = mergeHulls(findHull(points, minPoint, maxPoint),
                        maxPoint,
                        findHull(points, maxPoint, minPoint));
    h3.insert(h3.end(), minPoint);
    return Region2D(pointsToSegments(h3));
}

