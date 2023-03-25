#include <iostream>
#include "ConvexHullGrahamScan.h"
#include "TestCases.h"

int main()
{
	printRegion2D(ConvexHullGrahamScan(Point2D(test1)));
	return 0;
}
