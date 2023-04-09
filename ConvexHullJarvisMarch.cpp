#include "ConvexHullJarvisMarch.h"
#include "Utilities.h"

// Inspired by https://en.wikipedia.org/wiki/Gift_wrapping_algorithm
Region2D ConvexHullJarvisMarch(Point2D pointset){
    std::vector<SimplePoint2D>  points, hull;
    SimplePoint2D               pointOnHull, endpoint;

    if(pointset.count() < 3)
        return Region2D(); // no convex hull; return empty region
    points = Point2DToVector(pointset);

    /* initialize pointOnHull to leftmost point */
    pointOnHull = points[0];
    for(SimplePoint2D p : points)
        if(p.x <= pointOnHull.x)
            pointOnHull = p;

    do {
        endpoint = points[0];
        for (SimplePoint2D p : points)
            if (endpoint == pointOnHull ||
            isCounterClockwiseTurn(pointOnHull, endpoint, p) ||
            (areCollinear(pointOnHull, endpoint, p) &&
             distSquared(pointOnHull, endpoint) < distSquared(pointOnHull, p)))
                endpoint = p;

        hull.push_back(pointOnHull);
        pointOnHull = endpoint;
    } while (endpoint != hull[0]);

    return Region2D(pointsToSegments(hull));
}
