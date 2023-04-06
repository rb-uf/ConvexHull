#include <iostream>
#include <chrono>
#include "ConvexHullGrahamScan.h"
#include "ConvexHullJarvisMarch.h"
#include "ConvexHullMonotoneChain.h"
#include "ConvexHullDivideandConquer.h"
#include "TestCases.h"
#include "Utilities.h"

vector<SimplePoint2D> randomVectorSimplePoint2D(long count, int minX, int maxX, int minY, int maxY)
{
    generateSeed();
    std::vector<SimplePoint2D> points;
    for (long i = 0; i < count; i++)
        points.push_back(randomSimplePoint2D(minX, maxX, minY, maxY));
    return points;
}

void runTestAndPrint(vector<SimplePoint2D> p)
{
    cout << "Graham Scan" << endl;
    ConvexHullGrahamScan(Point2D(p, true, false)).print();
    cout << "Monotone Chain" << endl;
    ConvexHullMonotoneChain(Point2D(p, true, false)).print();
    cout << "Jarvis March" << endl;
    ConvexHullJarvisMarch(Point2D(p, true, false)).print();
    cout << "Divide and Conquer" << endl;
    ConvexHullDivideandConquer(Point2D(p, true, false)).print();
}

double getTime()
{
    auto t = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(t.time_since_epoch()).count();
}

void runTestAndTime(vector<SimplePoint2D> p)
{
    double start, stop;

    start = getTime();
    Region2D r1 = ConvexHullGrahamScan(Point2D(p, true, false));
    stop = getTime();
    cout << "GrahamScan runtime: " << (stop - start) << endl;

    start = getTime();
    Region2D r2 = ConvexHullMonotoneChain(Point2D(p, true, false));
    stop = getTime();
    cout << "MonotoneChain runtime: " << (stop - start) << endl;

    start = getTime();
    Region2D r3 = ConvexHullJarvisMarch(Point2D(p, true, false));
    stop = getTime();
    cout << "JarvisMarch runtime: " << (stop - start) << endl;

    start = getTime();
    Region2D r4 = ConvexHullDivideandConquer(Point2D(p, true, false));
    stop = getTime();
    cout << "DivideandConquer runtime: " << (stop - start) << endl;

    cout << endl;
    cout << "GrahamScan and MonotoneChain output " << (r1 == r2 ? "matches." : "doesn't match.") << endl;
    cout << "GrahamScan and JarvisMarch output " << (r1 == r3 ? "matches." : "doesn't match.") << endl;
    cout << "GrahamScan and DivideandConquer output " << (r1 == r4 ? "matches." : "doesn't match.") << endl;
}

int main()
{
    cout << "-------- test1 --------" << endl;
    runTestAndPrint(test1);
    cout << endl;

    cout << "-------- test2 --------" << endl;
    runTestAndPrint(test2);
    cout << endl;

    cout << "-------- test3: 100 points --------" << endl;
    runTestAndTime(randomVectorSimplePoint2D(100, 0, 500, 0, 500));
    cout << endl;

    cout << "-------- test4: 500 points --------" << endl;
    runTestAndTime(randomVectorSimplePoint2D(500, 0, 500, 0, 500));
    cout << endl;

    cout << "-------- test5: 1000 points --------" << endl;
    runTestAndTime(randomVectorSimplePoint2D(1000, 0, 500, 0, 500));
    cout << endl;

    return 0;
}

