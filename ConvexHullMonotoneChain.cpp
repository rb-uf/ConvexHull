#include <vector>
#include <algorithm>
#include <iostream>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Segment2D.h"
#include "Region2D.h"
#include "Point2D.h"
#include "Utilities.h"

Region2D ConvexHullMonotoneChain(Point2D Point2D_points)
{
    Point2D_points.sort();
    std::vector<SimplePoint2D> points = Point2DToVector(Point2D_points);

    if (points.size() <= 3)
        return pointsToSegments(points);

    // sort the points according to their standard ordering
    std::sort(points.begin(), points.end());

    std::vector<SimplePoint2D> lowerHull;
    for (int i = 0; i < points.size(); i++) {
        while (lowerHull.size() > 1 && isCounterClockwiseTurn(lowerHull[lowerHull.size()-2], lowerHull.back(), points[i]) <= 0)
            lowerHull.pop_back();
        lowerHull.push_back(points[i]);
    }
    lowerHull.pop_back();

    // repeat for upperHull, but in reverse
    std::vector<SimplePoint2D> upperHull;
    for (int i = points.size() - 1; i >= 0; i--) {
        while (upperHull.size() > 1 && isCounterClockwiseTurn(upperHull[upperHull.size()-2], upperHull.back(), points[i]) <= 0)
            upperHull.pop_back();
        upperHull.push_back(points[i]);
    }
    upperHull.pop_back();

    lowerHull.insert(lowerHull.end(), upperHull.begin(), upperHull.end()); // concatenate the vectors
    return Region2D(pointsToSegments(lowerHull));
}

