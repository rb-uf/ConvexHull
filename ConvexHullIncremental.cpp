#include "ConvexHullIncremental.h"
#include "ConvexHullDivideandConquer.h"
#include "ConvexHullJarvisMarch.h"
#include <iostream>
#include <algorithm>

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

vector<SimplePoint2D> simpleHull(vector<SimplePoint2D> points)
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
        hull = simpleHull(hull);
    }

    if(points.size() == 3)
    {
        return pointsToRegion(points);
    }
    
    int upperTangent;
    int lowerTangent;


    for(int j = 3; j < points.size(); j++)
    {
        
        vector<SimplePoint2D> tmpHull;
        upperTangent = hull.size()-1;
        lowerTangent = hull.size()-1;
        
        
        while(orientation(points[j],hull[upperTangent],hull[(upperTangent-1)%hull.size()]) >= Number("0"))
        {
            
            upperTangent = (upperTangent-1)%hull.size();
        }

        while(orientation(points[j],hull[lowerTangent],hull[(lowerTangent+1)%hull.size()]) <= Number("0"))
        {
            
            lowerTangent = (lowerTangent+1)%hull.size();
        }

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

    for(int k=0; k<hull.size(); k++){
        cout<<"("<<hull[k].x<<", "<<hull[k].y<<")"<<" ";
    }
    cout<<endl;

    return pointsToRegion(hull);
}