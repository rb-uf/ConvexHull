#include <vector>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Point2D.h"
#include "Segment2D.h"
#include "Region2D.h"

Number distSquared(SimplePoint2D a, SimplePoint2D b);
SimplePoint2D relativeCoord(SimplePoint2D origin, SimplePoint2D p);
std::vector<SimplePoint2D> Point2DToVector(Point2D Point2D_points);

Number orientation(SimplePoint2D p, SimplePoint2D q, SimplePoint2D r);

vector<SimplePoint2D> clockwiseHull(vector<SimplePoint2D> points);

bool isCounterClockwiseTurn(SimplePoint2D p1, SimplePoint2D p2, SimplePoint2D p3);

std::vector<Segment2D> pointsToSegments(std::vector<SimplePoint2D> points);
