#include "ConvexHullDivideandConquer.h"
#include "Utilities.h"
#include <algorithm>
#include <iostream>
using namespace std;

static Number zero = Number("0");

vector<SimplePoint2D> internalComputeHull(vector<SimplePoint2D> points)
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
            if(orientation(points[p], points[j], points[q]) > zero)
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

vector<SimplePoint2D> merge(vector<SimplePoint2D> hullA, vector<SimplePoint2D> hullB)
{
    bool done = false;
    int tmp = 0;
    for(int i=0; i<hullA.size(); i++){
        if(hullA[i] > hullA[tmp]){
            tmp = i;
        }
    }
    int a_uppertangent = tmp;
    int a_lowertangent = tmp;
    int b_uppertangent = 0;
    int b_lowertangent = 0;

    while(!done)
    {

        done = true;
        while(orientation(hullB[b_uppertangent],hullA[a_uppertangent],hullA[(a_uppertangent - 1 + hullA.size()) % hullA.size()]) >= zero)
        {
            a_uppertangent = (a_uppertangent - 1 + hullA.size()) % hullA.size();
        }
        while(orientation(hullA[a_uppertangent],hullB[b_uppertangent],hullB[(b_uppertangent + 1) % hullB.size()]) <= zero)
        {
            b_uppertangent = (b_uppertangent + 1) % hullB.size();
            done = false;
        }
    }
    done = false;
    while(!done)
    {
        done = true;
        while(orientation(hullA[a_lowertangent],hullB[b_lowertangent],hullB[(b_lowertangent - 1 + hullB.size()) % hullB.size()]) >= zero)
        {
            b_lowertangent = (b_lowertangent - 1 + hullB.size()) % hullB.size();
        }
        while(orientation(hullB[b_lowertangent],hullA[a_lowertangent],hullA[(a_lowertangent + 1) % hullA.size()]) <= zero)
        {
            a_lowertangent = (a_lowertangent + 1) % hullA.size();
            done = false;
        }
    }

    vector<SimplePoint2D> hull;
    for(int j=0; j<=a_uppertangent; j++)
    {
        hull.push_back(hullA[j]);
    }
    for(int k=b_uppertangent; k%hullB.size()!=b_lowertangent; k++)
    {
        hull.push_back(hullB[k%hullB.size()]);
    }
    hull.push_back(hullB[b_lowertangent]);
    for(int n = a_lowertangent; n%hullA.size()!=0; n++)
    {
        hull.push_back(hullA[n%hullA.size()]);
    }

    return hull;

}


vector<SimplePoint2D> internalRecursion(vector<SimplePoint2D> pointset)
{
    if(pointset.size() <= 5){
        return internalComputeHull(pointset);
    }

    int med = pointset.size() / 2;
    vector<SimplePoint2D> A(&pointset[0],&pointset[med]);
    vector<SimplePoint2D> B(&pointset[med],&pointset[pointset.size()]);
    return merge(internalRecursion(A),internalRecursion(B));
}

Region2D ConvexHullDivideandConquer(Point2D pointset)
{
    pointset.sort();

    vector<SimplePoint2D> points;
    for(Point2D::Iterator iter = pointset.begin(); iter != pointset.end(); iter++)
    {
        points.push_back(*iter);

    }

    if(points.size() < 3)
    {
        cout<<"Not enough points for hull"<<endl;
        return Region2D();
    }

    vector<SimplePoint2D> hull;

    hull = internalRecursion(points);
/*
    for(int k=0; k<hull.size(); k++){
       cout<<"("<<hull[k].x<<", "<<hull[k].y<<")"<<endl;
    }
*/
    vector<Segment2D> hullSegments;

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
