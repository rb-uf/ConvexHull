#include "ConvexHullJarvisMarch.h"
#include "Utilities.h"
#include <iostream>
using namespace std;

static Number zero = Number("0");

Region2D ConvexHullJarvisMarch(Point2D pointset){
    vector<SimplePoint2D> points;
    
    for(Point2D::Iterator ptr = pointset.begin(); ptr != pointset.end(); ptr++)
    {
        points.push_back(*ptr);
    }

    if(pointset.count() < 3)
    {
        return Region2D();
    }

    vector<SimplePoint2D> hull;

    //Find leftmost point, this is guaranteed to be in the hull
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
        //Calculate the point that makes the leftmost turn from the leftmost point and add it to the hull
        for(int j = 0; j < points.size(); j++)
        {
            if(orientation(points[p], points[j], points[q]) < zero)
            {
                q = j;
            }
            //Handles collinear points by adding point which is the father distance from p
            else if(orientation(points[p],points[j],points[q]) == zero)
            {
                if(distSquared(points[p],points[j]) > distSquared(points[q],points[p]))
                {
                    q = j;
                }
            }
            
        }
        p = q;
        if(p == left)
        {
            finish++;
        }
        q = (p + 1) % points.size();
    }

    vector<Segment2D> hullSegments;

    // Form hull segments and push into vector

    for(int n=0; n<hull.size(); n++){
        if(n == hull.size()-1){
            hullSegments.push_back(Segment2D(hull[n],hull[0]));
        }
        else
        {
            hullSegments.push_back(Segment2D(hull[n],hull[n+1]));
        }
        
    }

    return Region2D(hullSegments);
}
