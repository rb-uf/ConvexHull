#include <iostream>
#include "ConvexHullGrahamScan.h"
#include "ConvexHullJarvisMarch.h"
#include "ConvexHullMonotoneChain.h"
#include "TestCases.h"
#include "Utilities.h"

int main()
{
    cout << "-------- test1 --------" << endl;
    cout << "Graham Scan" << endl;
    printRegion2D(ConvexHullGrahamScan(Point2D(test1)));
    cout << "Monotone Chain" << endl;
    printRegion2D(ConvexHullMonotoneChain(Point2D(test1)));
    cout << "Jarvis March" << endl;
    printRegion2D(ConvexHullJarvisMarch(Point2D(test1)));
    cout << endl;

    cout << "-------- test2 --------" << endl;
    cout << "Graham Scan" << endl;
    printRegion2D(ConvexHullGrahamScan(Point2D(test2)));
    cout << "Monotone Chain" << endl;
    printRegion2D(ConvexHullMonotoneChain(Point2D(test2)));
    cout << "Jarvis March" << endl;
    printRegion2D(ConvexHullJarvisMarch(Point2D(test2)));
    cout << endl;

    return 0;
}

