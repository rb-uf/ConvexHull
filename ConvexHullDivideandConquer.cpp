#include "ConvexHullDivideandConquer.h"
#include "Utilities.h"
#include <algorithm>
#include <iostream>
using namespace std;

static Number zero = Number("0");

vector<SimplePoint2D> merge(vector<SimplePoint2D> hullA, vector<SimplePoint2D> hullB)
{
    cout << "DEBUG entering merge" << endl;
    bool done = false;
    int rightmost = 0;
    for(int i=0; i<hullA.size(); i++){
        if(hullA[i] > hullA[rightmost]){
            rightmost = i;
        }
    }
    cout << "DEBUG found rightmost" << endl;
    int a_uppertangent = rightmost;
    int a_lowertangent = rightmost;
    int b_uppertangent = 0;
    int b_lowertangent = 0;

    while (!done) {
        done = true;
        while(orientation(hullB[b_uppertangent],hullA[a_uppertangent],hullA[(a_uppertangent - 1 + hullA.size()) % hullA.size()]) >= zero)
        {
            if(hullA.size() == 2){
                if(hullA[0].y > hullA[1].y){a_uppertangent = 0;}
                else{a_uppertangent = 1;}
                break;
            }
            a_uppertangent = (a_uppertangent == 0) ? (hullA.size() - 1) : (a_uppertangent - 1);
        }
        while(orientation(hullA[a_uppertangent],hullB[b_uppertangent],hullB[(b_uppertangent + 1) % hullB.size()]) <= zero)
        {
            if(hullB.size() == 2){
                if(hullB[0].y > hullB[1].y){b_uppertangent = 0;}
                else{b_uppertangent = 1;}
                done = false;
                break;
            }
            b_uppertangent = (b_uppertangent >= hullB.size() - 1) ? (0) : (b_uppertangent + 1);
            done = false;
        }
        cout << "DEBUG loop1" << endl;
    }
    done = false;
    while(!done)
    {
        done = true;
        while(orientation(hullA[a_lowertangent],hullB[b_lowertangent],hullB[(b_lowertangent - 1 + hullB.size()) % hullB.size()]) >= zero)
        {
            if(hullB.size() == 2){
                if(hullB[0].y < hullB[1].y){b_lowertangent = 0;}
                else{b_lowertangent = 1;}
                break;
            }
            b_lowertangent = (b_lowertangent == 0) ? (hullB.size() - 1) : (b_lowertangent - 1);
            cout << "DEBUG loop3" << endl;

        }
        while(orientation(hullB[b_lowertangent],hullA[a_lowertangent],hullA[(a_lowertangent + 1) % hullA.size()]) <= zero)
        {
            if(hullA.size() == 2){
                if(hullA[0].y < hullA[1].y){a_lowertangent = 0;}
                else{a_lowertangent = 1;}
                done = false;
                break;
            }
            a_lowertangent = (a_lowertangent >= hullA.size() - 1) ? (0) : (a_lowertangent + 1);
            done = false;
            cout << "DEBUG loop4" << endl;
        }
        cout << "DEBUG loop2" << endl;
    }
    cout << "DEBUG out of loop2" << endl;

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
    cout << "DEBUG end of merge" << endl;

    return hull;

}

vector<SimplePoint2D> removeColinear(vector<SimplePoint2D> points)
{
    cout << "DEBUG start removeColinear" << endl;

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

vector<SimplePoint2D> internalRecursion(vector<SimplePoint2D> pointset)
{
    cout << "DEBUG enter internalRecursion" << endl;

    if(pointset.size() <= 5)
        return clockwiseHull(pointset);

    cout << "DEBUG before size" << endl;
    int med = pointset.size() / 2;
    cout << "DEBUG copy vectors start" << endl;
    vector<SimplePoint2D> A(&pointset[0],&pointset[med]);
    vector<SimplePoint2D> B(&pointset[med],&pointset[pointset.size()]);
    cout << "DEBUG end of internalRecursion" << endl;
    return merge(internalRecursion(A),internalRecursion(B));
}


Region2D ConvexHullDivideandConquer(Point2D pointset)
{
    pointset.sort();

    vector<SimplePoint2D> points = Point2DToVector(pointset);

    if(points.size() < 3)
        return Region2D();

    vector<SimplePoint2D> hull1 = internalRecursion(points);
    cout << "DEBUG Recursion over." << endl;
    vector<SimplePoint2D> hull = removeColinear(hull1);
/*
    for (SimplePoint2D p : hull)
        p.print();
*/
    return Region2D(pointsToSegments(hull));
}
