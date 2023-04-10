#include <iostream>
#include "ConvexHullGrahamScan.h"
#include "ConvexHullMonotoneChain.h"
#include "ConvexHullJarvisMarch.h"
#include "ConvexHullDivideandConquer.h"
#include "ConvexHullIncremental.h"
#include "ConvexHullQuickhull.h"
#include "TestCases.h"
#include "Utilities.h"

void runTestAndPrint(vector<SimplePoint2D> p)
{
    cout << "Monotone Chain" << endl;
    ConvexHullMonotoneChain(Point2D(p, true, false)).print();
    cout << "Graham Scan" << endl;
    ConvexHullGrahamScan(Point2D(p, true, false)).print();
    cout << "Jarvis March" << endl;
    ConvexHullJarvisMarch(Point2D(p, true, false)).print();
//    cout << "Divide and Conquer" << endl;
//    ConvexHullDivideandConquer(Point2D(p, true, false)).print();
//    cout << "Incremental" << endl;
//    ConvexHullIncremental(Point2D(p, true, false)).print();
    cout << "Quickhull" << endl;
    ConvexHullQuickhull(Point2D(p, true, false)).print();
}

void runTestAndTime(vector<SimplePoint2D> p)
{
    double start, stop;

    start = getTime();
    Region2D r1 = ConvexHullMonotoneChain(Point2D(p, true, false));
    stop = getTime();
    cout << "MonotoneChain runtime: " << (stop - start) << endl;

    start = getTime();
    Region2D r2 = ConvexHullGrahamScan(Point2D(p, true, false));
    stop = getTime();
    cout << "GrahamScan runtime: " << (stop - start) << endl;

    start = getTime();
    Region2D r3 = ConvexHullJarvisMarch(Point2D(p, true, false));
    stop = getTime();
    cout << "JarvisMarch runtime: " << (stop - start) << endl;
/*
    start = getTime();
    Region2D r4 = ConvexHullDivideandConquer(Point2D(p, true, false));
    stop = getTime();
    cout << "DivideandConquer runtime: " << (stop - start) << endl;

    start = getTime();
    Region2D r5 = ConvexHullIncremental(Point2D(p, true, false));
    stop = getTime();
    cout << "Incremental runtime: " << (stop - start) << endl;
*/
    start = getTime();
    Region2D r6 = ConvexHullQuickhull(Point2D(p, true, false));
    stop = getTime();
    cout << "Quickhull runtime: " << (stop - start) << endl;

    cout << endl;
    cout << "MonotoneChain and GrahamScan output " << (r1 == r2 ? "matches." : "doesn't match.") << endl;
    cout << "MonotoneChain and JarvisMarch output " << (r1 == r3 ? "matches." : "doesn't match.") << endl;
//    cout << "MonotoneChain and DivideandConquer output " << (r1 == r4 ? "matches." : "doesn't match.") << endl;
//    cout << "MonotoneChain and Incremental output " << (r1 == r5 ? "matches." : "doesn't match.") << endl;
    cout << "MonotoneChain and Quickhull output " << (r1 == r6 ? "matches." : "doesn't match.") << endl;
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

    cout << "-------- test5: 100000 points --------" << endl;
    runTestAndTime(randomVectorSimplePoint2D(100000, 0, 500, 0, 500));
    cout << endl;

    return 0;
}

