#include "ConvexHullDivideandConquer.h"
#include "Utilities.h"
#include <algorithm>
#include <iostream>
using namespace std;

static Number zero = Number("0");

vector<SimplePoint2D> merge(vector<SimplePoint2D> hullA, vector<SimplePoint2D> hullB)
{
    bool done = false;
    int rightmost = 0;
    for(int i=0; i<hullA.size(); i++){
        if(hullA[i] > hullA[rightmost]){
            rightmost = i;
        }
    }
    int a_uppertangent = rightmost;
    int a_lowertangent = rightmost;
    int b_uppertangent = 0;
    int b_lowertangent = 0;

    while (!done) {
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
    if(pointset.size() <= 5)
        return clockwiseHull(pointset);

    int med = pointset.size() / 2;
    vector<SimplePoint2D> A(&pointset[0],&pointset[med]);
    vector<SimplePoint2D> B(&pointset[med],&pointset[pointset.size()]);
    return merge(internalRecursion(A),internalRecursion(B));
}

vector<SimplePoint2D> removeColinear(vector<SimplePoint2D> points)
{
    vector<SimplePoint2D> newPoints;
    int size = points.size();

    newPoints.push_back(points[0]);

    for (int i = 1; i < size - 1; i++)
        if (!areCollinear(points[i-1], points[i], points[i+1]))
            newPoints.push_back(points[i]);

    if (!areCollinear(points[size - 2], points[size - 1], points[0]))
        newPoints.push_back(points[size - 1]);

    return newPoints;
}

Region2D ConvexHullDivideandConquer(Point2D pointset)
{
    pointset.sort();

    vector<SimplePoint2D> points = Point2DToVector(pointset);

    if(points.size() < 3)
        return Region2D();

    vector<SimplePoint2D> hull = removeColinear(internalRecursion(points));
/*
    for (SimplePoint2D p : hull)
        p.print();
*/
    return Region2D(pointsToSegments(hull));
}
