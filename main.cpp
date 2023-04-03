#include <iostream>
#include <chrono>
#include "ConvexHullGrahamScan.h"
#include "ConvexHullJarvisMarch.h"
#include "ConvexHullMonotoneChain.h"
#include "TestCases.h"
#include "Utilities.h"

void runTestAndPrint(Point2D p)
{
    cout << "Graham Scan" << endl;
    ConvexHullGrahamScan(p).print();
    cout << "Monotone Chain" << endl;
    ConvexHullMonotoneChain(p).print();
    cout << "Jarvis March" << endl;
    ConvexHullJarvisMarch(p).print();
}

double getTime()
{
    auto t = std::chrono::high_resolution_clock::now();
    return std::chrono::duration<double>(t.time_since_epoch()).count();
}

void runTestAndTime(Point2D p)
{
    double start, stop, t1, t2, t3;

    start = getTime();
    Region2D r1 = ConvexHullGrahamScan(p);
    stop = getTime();
    t1 = stop - start;

    start = getTime();
    Region2D r2 = ConvexHullMonotoneChain(p);
    stop = getTime();
    t2 = stop - start;

    start = getTime();
    Region2D r3 = ConvexHullJarvisMarch(p);
    stop = getTime();
    t3 = stop - start;

    if (!(r1 == r2 && r2 == r3)) {
        cout << "Convex hull outputs do not match." << endl;
    } else {
        cout << "Convex hull outputs match." << endl;
        cout << "    GrahamScan runtime:    " << t1 << endl;
        cout << "    MonotoneChain runtime: " << t2 << endl;
        cout << "    JarvisMarch runtime:   " << t3 << endl;
    }
}

int main()
{
    cout << "-------- test1 --------" << endl;
    runTestAndPrint(Point2D(test1));
    cout << endl;

    cout << "-------- test2 --------" << endl;
    runTestAndPrint(Point2D(test2));
    cout << endl;

    cout << "-------- test3: 100 points --------" << endl;
    runTestAndTime(randomPoint2D(100, 0, 500, 0, 500));
    cout << endl;

    cout << "-------- test4: 500 points --------" << endl;
    runTestAndTime(randomPoint2D(500, 0, 500, 0, 500));
    cout << endl;

    cout << "-------- test5: 1000 points --------" << endl;
    runTestAndTime(randomPoint2D(1000, 0, 500, 0, 500));
    cout << endl;

    return 0;
}

