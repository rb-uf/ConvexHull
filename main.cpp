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
    ConvexHullGrahamScan(Point2D(test1)).print();
    cout << "Monotone Chain" << endl;
    ConvexHullMonotoneChain(Point2D(test1)).print();
    cout << "Jarvis March" << endl;
    ConvexHullJarvisMarch(Point2D(test1)).print();
    cout << endl;

    cout << "-------- test2 --------" << endl;
    cout << "Graham Scan" << endl;
    ConvexHullGrahamScan(Point2D(test2)).print();
    cout << "Monotone Chain" << endl;
    ConvexHullMonotoneChain(Point2D(test2)).print();
    cout << "Jarvis March" << endl;
    ConvexHullJarvisMarch(Point2D(test2)).print();
    cout << endl;

    return 0;
}

