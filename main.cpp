#include <iostream>
#include "ConvexHullGrahamScan.h"
#include "TestCases.h"

int main()
{
	cout << "test1" << endl;
	printRegion2D(ConvexHullGrahamScan(Point2D(test1)));
	cout << endl;

	cout << "test2" << endl;
	printRegion2D(ConvexHullGrahamScan(Point2D(test2)));
	cout << endl;

	return 0;
}

