#include "ConvexHullIncremental.h"
#include "Utilities.h"
#include <iostream>
#include <algorithm>

static Number zero = Number("0");

Region2D pointsToRegion(vector<SimplePoint2D> points)
{
    vector<Segment2D> edges;

    for(int n=0; n<points.size(); n++){
        if(n == points.size()-1){
            edges.push_back(Segment2D(points[n],points[0]));
        }
        else
        {
            edges.push_back(Segment2D(points[n],points[n+1]));
        }
        
    }

    return Region2D(edges);

}


Region2D ConvexHullIncremental(Point2D pointset)
{
    vector<SimplePoint2D> points;
    for(Point2D::Iterator itr = pointset.begin(); itr != pointset.end(); itr++)
    {
        points.push_back(*itr);
    }

    if(!pointset.isOrdered())
    {
        sort(points.begin(),points.end());
    }

    vector<SimplePoint2D> hull;

    if(points.size() < 3)
    {
        return Region2D();
    }


    for(int i=0; i<3; i++)
    {
        hull.push_back(points[i]);
    }

    //Find hull of first 3 points in sorted vector
    hull = clockwiseHull(hull);


    if(points.size() == 3)
    {
        return pointsToRegion(points);
    }
    
    int upperTangent = 0;
    int lowerTangent = 0;
    vector<SimplePoint2D> tmpHull;

    //Incrementally add points to hull while maintaining hull requirements;
    for(int j = 3; j < points.size(); j++)
    {
 
        tmpHull.clear();
        upperTangent = (upperTangent+1)%hull.size();
        lowerTangent = upperTangent;

        //Find Upper Tangent to next leftmost point in sorted vector
        while(orientation(points[j],hull[upperTangent],hull[(upperTangent-1+hull.size())%hull.size()]) <= zero)
        {
            upperTangent = (upperTangent-1+hull.size())%hull.size();
        }

        //Find Lower Tangent to next leftmost point in sorted vector
        while(orientation(points[j],hull[lowerTangent],hull[(lowerTangent+1)%hull.size()]) >= zero)
        {
            lowerTangent = (lowerTangent+1)%hull.size();
        }

        //Push back hull points in to vector and ignore points that are within the region formed by tangents
        for(int k = 0; k <= upperTangent; k++)
        {

            tmpHull.push_back(hull[k]);
        }


        tmpHull.push_back(points[j]);

        for(int n = lowerTangent; n%hull.size()!= 0; n++){

            tmpHull.push_back(hull[n%hull.size()]);
        }

        hull = tmpHull;
        
    }


    return pointsToRegion(hull);
}
