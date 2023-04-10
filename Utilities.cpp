#include <iostream>
#include "Utilities.h"

Number distSquared(SimplePoint2D a, SimplePoint2D b)
{
    return (a.x - b.x).square() + (a.y - b.y).square();
}

Number orientation(SimplePoint2D p, SimplePoint2D q, SimplePoint2D r)
{   
    Number turn = (q.y - p.y) * (r.x -q.x) - (q.x - p.x) * (r.y - q.y);
    return turn;
}

SimplePoint2D relativeCoord(SimplePoint2D origin, SimplePoint2D p)
{
    return SimplePoint2D(p.x - origin.x, p.y - origin.y);
}

vector<SimplePoint2D> clockwiseHull(vector<SimplePoint2D> points)
{
    vector<SimplePoint2D> hull;
    int left = 0;
    for(int i = 1; i < points.size(); i++)
    {
        if(points[i].x <= points[left].x)
        {
            left = i;
        }
    }

    int p = left;
    int q = (p + 1) % points.size();
    int finish = 0;
    while(finish < 1)
    {
        hull.push_back(points[p]);
        for(int j = 0; j < points.size(); j++)
        {
            if(orientation(points[p], points[j], points[q]) > Number("0"))
            {
                q = j;
            }
            
        }
        p = q;
        if(p == left)
        {
            finish++;
        }
        q = (p + 1) % points.size();
    }

    return hull;
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
