#include <iostream>
#include <chrono>
#include "Utilities.h"

static Number zero = Number();

Number distSquared(const SimplePoint2D& a, const SimplePoint2D& b)
{
    return (a.x - b.x).square() + (a.y - b.y).square();
}

SimplePoint2D relativeCoord(const SimplePoint2D& origin, const SimplePoint2D& p)
{
    return SimplePoint2D(p.x - origin.x, p.y - origin.y);
}

vector<SimplePoint2D> clockwiseHull(vector<SimplePoint2D> points)
{
    vector<SimplePoint2D> hull;
    int left = 0;
    for(int i = 1; i < points.size(); i++)
        if(points[i].x <= points[left].x)
            left = i;

    int p = left;
    int q = (p + 1) % points.size();

    while (true) {
        hull.push_back(points[p]);
        for(int j = 0; j < points.size(); j++)
            if(orientation(points[p], points[j], points[q]) > zero)
                q = j;
            else if(orientation(points[p],points[j],points[q]) == Number("0"))
            {
                if(distSquared(points[p],points[j]) > distSquared(points[q],points[p]))
                {
                    q = j;
                }
            }

        p = q;
        if(p == left)
            break;

        q = (p + 1) % points.size();
    }

    return hull;
}

std::vector<SimplePoint2D> Point2DToVector(const Point2D& p2D)
{
    std::vector<SimplePoint2D> points;
    for (SimplePoint2D p : p2D)
        points.push_back(p);
    return points;
}


// Converts an vector of SimplePoint2D into a vector of Segment2Ds.
// Segments connect one point to the next, according to the ordering of the points.
// If the first and last point are not equal, a segment will be drawn between them as well.
std::vector<Segment2D> pointsToSegments(const std::vector<SimplePoint2D>& points)
{
    std::vector<Segment2D> segments;

    for (int i = 0; i < points.size()-1; i++)
        segments.push_back(Segment2D(points[i], points[i+1]));

    if (points.front() != points.back())
        segments.push_back(Segment2D(points.front(), points.back()));

    return segments;
}


/* orientation: based on cross-products */
Number orientation(const SimplePoint2D& p, const SimplePoint2D& q, const SimplePoint2D& r)
{
    return (q.x - p.x) * (r.y - q.y) - (r.x - q.x) * (q.y - p.y);
//    return (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
}
bool isCounterClockwiseTurn(const SimplePoint2D& p, const SimplePoint2D& q, const SimplePoint2D& r)
{
    return orientation(p, q, r) > zero;
}
bool areCollinear(const SimplePoint2D& p, const SimplePoint2D& q, const SimplePoint2D& r)
{
    return orientation(p, q, r) == zero;
}

double getTime()
{
    auto t = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(t.time_since_epoch()).count();
}

vector<SimplePoint2D> randomVectorSimplePoint2D(long count, int minX, int maxX, int minY, int maxY)
{
    generateSeed();
    std::vector<SimplePoint2D> points;
    for (long i = 0; i < count; i++)
        points.push_back(randomSimplePoint2D(minX, maxX, minY, maxY));
    return points;
}
