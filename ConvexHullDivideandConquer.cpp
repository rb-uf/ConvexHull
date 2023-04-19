#include "ConvexHullDivideandConquer.h"
#include "Utilities.h"
#include <algorithm>
#include <iostream>
#include <fstream>
using namespace std;

static Number zero = Number("0");


vector<SimplePoint2D> merge(vector<SimplePoint2D> hullA, vector<SimplePoint2D> hullB)
{
    // Find rightmost point of Hull A and leftmost point of Hull B is 0
    bool done = false;
    int rightmost = 0;
    for(int i=0; i<hullA.size(); i++){
        if(hullA[i] > hullA[rightmost]){
            rightmost = i;
        }
    }
    //cout << "DEBUG found rightmost" << endl;
    int a_uppertangent = rightmost;
    int a_lowertangent = rightmost;
    int b_uppertangent = 0;
    int b_lowertangent = 0;
    
    // Find Upper Tangent
    while (!done) {
        done = true;
        //Find point on Hull A that forms part of Upper Tangent
        while(orientation(hullB[b_uppertangent],hullA[a_uppertangent],hullA[(a_uppertangent - 1 + hullA.size()) % hullA.size()]) <= zero)
        {
            //If hull is a set of two points then tangent points are trivial to figure
            if(hullA.size() == 2){
                if(hullA[0].y > hullA[1].y){a_uppertangent = 0;}
                else{a_uppertangent = 1;}
                break;
            }
            a_uppertangent = (a_uppertangent - 1 + hullA.size()) % hullA.size();
        }
        //Find point on Hull B that forms part of Upper Tangent
        while(orientation(hullA[a_uppertangent],hullB[b_uppertangent],hullB[(b_uppertangent + 1) % hullB.size()]) >= zero)
        {

            if(hullB.size() == 2){
                if(hullB[0].y > hullB[1].y){b_uppertangent = 0;}
                else{b_uppertangent = 1;}
                done = false;
                break;
            }
            b_uppertangent = (b_uppertangent + 1) % hullB.size();
            done = false;
        }
    }
    done = false;

    //Find Lower Tangent
    while(!done)
    {

        done = true;
        //Find point on Hull B that forms part of the lower tangent
        while(orientation(hullA[a_lowertangent],hullB[b_lowertangent],hullB[(b_lowertangent - 1 + hullB.size()) % hullB.size()]) <= zero)
        {
            if(hullB.size() == 2){
                if(hullB[0].y < hullB[1].y){b_lowertangent = 0;}
                else{b_lowertangent = 1;}
                break;
            }
            b_lowertangent = (b_lowertangent - 1 + hullB.size()) % hullB.size();

        }
        // Find point on Hull A that forms part of the lower tangent
        while(orientation(hullB[b_lowertangent],hullA[a_lowertangent],hullA[(a_lowertangent + 1) % hullA.size()]) >= zero)
        {
            if(hullA.size() == 2){
                if(hullA[0].y < hullA[1].y){a_lowertangent = 0;}
                else{a_lowertangent = 1;}
                done = false;
                break;
            }
            a_lowertangent = (a_lowertangent + 1) % hullA.size();
            done = false;
        }
    }

    //Merge Hull A and B by going clockwise over all the point and ignoring points that are within the tangents
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

//Main recursive body
vector<SimplePoint2D> internalRecursion(vector<SimplePoint2D> pointset)
{
    //Base case for when point sizes are less than 5 to prevent special cases that may cause failure
    if(pointset.size() <= 5) {
        return clockwiseHull(pointset);
    }
    //Splits sorted array into halves, recursively computes hulls for halfs and then merges hulls together
    int med = pointset.size() / 2;
    vector<SimplePoint2D> A(&pointset[0],&pointset[med]);
    vector<SimplePoint2D> B(&pointset[med],&pointset[pointset.size()]);
    return merge(internalRecursion(A),internalRecursion(B));
}

//Removes Collinear points by checking if points along the hull are collinear and then deleting.
vector<SimplePoint2D> removeColinear(vector<SimplePoint2D> points)
{
    //cout << "DEBUG start removeColinear" << endl;

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
    //cout << "DEBUG enter internalRecursion" << endl;

    if(pointset.size() <= 5)
        return clockwiseHull(pointset);

    //cout << "DEBUG before size" << endl;
    int med = pointset.size() / 2;
    //cout << "DEBUG copy vectors start" << endl;
    vector<SimplePoint2D> A(&pointset[0],&pointset[med]);
    vector<SimplePoint2D> B(&pointset[med],&pointset[pointset.size()]);
    //cout << "DEBUG end of internalRecursion" << endl;
    return merge(internalRecursion(A),internalRecursion(B));
}


Region2D ConvexHullDivideandConquer(Point2D pointset)
{

    pointset.sort();

    vector<SimplePoint2D> points = Point2DToVector(pointset);


    if(points.size() < 3)
        return Region2D();

    //Calls internal recursive method to implement Divide and Conquer
    vector<SimplePoint2D> hull = internalRecursion(points);


    return Region2D(pointsToSegments(hull));
}
