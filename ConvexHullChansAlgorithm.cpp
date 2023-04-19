#include "ConvexHullChansAlgorithm.h"
#include "Utilities.h"
#include <algorithm>
#include <cmath>
#include <vector>
#include <iostream>
using namespace std;


static Number zero = Number("0");

Number angleFactor(SimplePoint2D sp)
{
    if (sp.x == zero && sp.y == zero)
        return Number("2");     // the origin is always first
    return sp.x.sign() * (sp.x.square() / (sp.x.square() + sp.y.square()));
}

vector<SimplePoint2D> internalGrahamScan(vector<SimplePoint2D> pointset, int start, int end)
{
    vector<SimplePoint2D> points(&pointset[start],&pointset[end]);

    /* Let p0 be the point with the lowest y-coord and lowest x-coord (in that order) */
    SimplePoint2D p0 = points[0];
    for (SimplePoint2D p : points)
        if ((p.y < p0.y) || (p.y == p0.y && p.x < p0.x))
            p0 = p;

    /* A lambda function that compares the angles of p1 and p2 relative to p0. */
    SimplePoint2D origin = SimplePoint2D(zero, zero);
    auto comp = [&p0, &origin](SimplePoint2D p1, SimplePoint2D p2) {
        if (p0 == p2)
            return false;
        if (p0 == p1)
            return true;

        Number a1 = angleFactor(relativeCoord(p0, p1));
        Number a2 = angleFactor(relativeCoord(p0, p2));

        if (a1 != a2)
            return a1 > a2;
        else
            return distSquared(origin, p1) < distSquared(origin, p2);
    };

    // Sort points by polar angle with p0
    std::sort(points.begin(), points.end(), comp);



    std::vector<SimplePoint2D> stack;
    for (SimplePoint2D p : points) {
        while (stack.size() > 1 && isCounterClockwiseTurn(stack[stack.size()-2], stack.back(), p) <= 0) {
            stack.pop_back();
        }
        stack.push_back(p);
    }


    return stack;

}

pair<bool,vector<SimplePoint2D>> partialHull(vector<SimplePoint2D> points, int m){
    int k = ceil(points.size() / m);
    vector<vector<SimplePoint2D>> subHulls;
    int start;
    int end;
    for(int i=0; i<k; i++){
        start = i*m;
        end = i*m + m;
        if(end > points.size()){end = points.size();}
        subHulls[i] = internalGrahamScan(points,start,end);
    }

    int bottomMost = 0;
    for(int k=1; k<points.size(); k++){
        if((points[k].y < points[bottomMost].y) || (points[k].y == points[bottomMost].y && points[k].x > points[bottomMost].x)){
            bottomMost = k;
        }
    }

    vector<int> prevTangents;
    for(int j=0; j<k; j++){
        prevTangents.push_back(0);
    }

    int p = bottomMost;
    int q;
    vector<SimplePoint2D> hull;
    bool correct = false;

    for(int a=0; a<m; a++){
        hull.push_back(points[p]);
        for(int b=0; b<k; b++){
            while(orientation(points[p],subHulls[k][prevTangents[k]],subHulls[k][(prevTangents[k]-1+subHulls[k].size())%subHulls[k].size()]) >= zero){
                prevTangents[k] = (prevTangents[k]-1+subHulls[k].size())%subHulls[k].size();
            }
        }
        q = 0;
        for(int c = 1; c < prevTangents.size(); c++){
            if(orientation(points[p],subHulls[c][prevTangents[c]],subHulls[q][prevTangents[q]]) > zero){
                q = c;
            }
            else if(orientation(points[p],subHulls[c][prevTangents[c]],subHulls[q][prevTangents[q]]) == zero){
                if(distSquared(points[p],subHulls[c][prevTangents[c]]) > distSquared(subHulls[q][prevTangents[q]], points[p])){
                    q = c;
                }
            }
        }
        p = q;
        if(p == bottomMost){
            correct = true;
            break;
        }
    }

    return make_pair(correct,hull);
    
}

Region2D ConvexHullChansAlgorithm(Point2D pointset)
{
    bool done = false;
    vector<SimplePoint2D> points;
    vector<SimplePoint2D> hull;
    pair<bool, vector<SimplePoint2D>> partial;

    for(Point2D::Iterator itr = pointset.begin(); itr != pointset.end(); itr++)
    {
        points.push_back(*itr);
    }

    if(points.size() < 3){
        return Region2D();
    }
    else if(points.size() == 3){
        return Region2D(pointsToSegments(points));
    }
    else{
        int count = 1;
        int m;
        while(!done)
        {
            m = min((int)pow(2,pow(2,count)), (int)points.size());
            partial = partialHull(points,m);
            if(partial.first){
                done = true;
            }
            count++;
        }
    }
    hull = partial.second;
    return Region2D(pointsToSegments(hull));
}
