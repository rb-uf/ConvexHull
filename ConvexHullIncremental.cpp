#include "ConvexHullIncremental.h"
#include "Utilities.h"
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

    for(int i=0; i<points.size(); i++){
        //cout<<"("<<points[i].x<<", "<<points[i].y<<")"<<endl;
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

    hull = clockwiseHull(hull);

    //for(SimplePoint2D sp: hull){
    //    cout<<sp.x<<" "<<sp.y<<endl;
    //}

    if(points.size() == 3)
    {
        return pointsToRegion(points);
    }
    
    int upperTangent = 0;
    int lowerTangent = 0;
    vector<SimplePoint2D> tmpHull;


    for(int j = 3; j < points.size(); j++)
    {
        //cout<<j<<": "<<points[j].x<<" "<<points[j].y<<endl;
        tmpHull.clear();
        upperTangent = (upperTangent+1)%hull.size();
        lowerTangent = upperTangent;
        //cout<<"Upper Tangent: ";
        while(orientation(points[j],hull[upperTangent],hull[(upperTangent-1+hull.size())%hull.size()]) >= Number("0"))
        {
            upperTangent = (upperTangent-1+hull.size())%hull.size();
        }
        //cout<<hull[upperTangent].x<<" "<<hull[upperTangent].y<<endl;
        //cout<<"Lower Tangent: ";
        while(orientation(points[j],hull[lowerTangent],hull[(lowerTangent+1)%hull.size()]) <= Number("0"))
        {
            lowerTangent = (lowerTangent+1)%hull.size();
        }
        //cout<<hull[lowerTangent].x<<" "<<hull[lowerTangent].y<<endl;
        //cout<<"Hull: ";
        for(int k = 0; k <= upperTangent; k++)
        {
            //cout<<hull[k].x<<" "<<hull[k].y<<"| ";
            tmpHull.push_back(hull[k]);
        }


        tmpHull.push_back(points[j]);
        //cout<<points[j].x<<" "<<points[j].y<<"| ";
        for(int n = lowerTangent; n%hull.size()!= 0; n++){
            //cout<<hull[n%hull.size()].x<<" "<<hull[n%hull.size()].y<<"| ";
            tmpHull.push_back(hull[n%hull.size()]);
        }
        //cout<<endl;
        hull = tmpHull;
        
    }

    for(int k=0; k<hull.size(); k++){
        cout<<"("<<hull[k].x<<", "<<hull[k].y<<")"<<endl;
    }

    return pointsToRegion(hull);
}
