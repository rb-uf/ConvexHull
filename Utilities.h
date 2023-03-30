#include <vector>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Point2D.h"
#include "Segment2D.h"
#include "Region2D.h"

#define ZERO Number("0")
#define ORIGIN SimplePoint2D(ZERO, ZERO)

Number square(Number n);
Number abs(Number n);
Number sign(Number n);

Number distSquared(SimplePoint2D a, SimplePoint2D b);
SimplePoint2D relativeCoord(SimplePoint2D origin, SimplePoint2D p);
std::vector<SimplePoint2D> Point2DToVector(Point2D Point2D_points);

void printSimplePoint2D(SimplePoint2D sp);
void printSegment2D(Segment2D s);
void printRegion2D(Region2D r);

bool isCounterClockwiseTurn(SimplePoint2D p1, SimplePoint2D p2, SimplePoint2D p3);
