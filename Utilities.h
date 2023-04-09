#include <vector>
#include "Number.h"
#include "SimplePoint2D.h"
#include "Point2D.h"
#include "Segment2D.h"
#include "Region2D.h"

Number distSquared(const SimplePoint2D& a, const SimplePoint2D& b);
SimplePoint2D relativeCoord(const SimplePoint2D& origin, const SimplePoint2D& p);
std::vector<SimplePoint2D> Point2DToVector(const Point2D& p2D);

bool isCounterClockwiseTurn(const SimplePoint2D& p1, const SimplePoint2D& p2, const SimplePoint2D& p3);

std::vector<Segment2D> pointsToSegments(const std::vector<SimplePoint2D>& points);
Number orientation(const SimplePoint2D& p, const SimplePoint2D& q, const SimplePoint2D& r);
Number crossProduct(const SimplePoint2D& p1, const SimplePoint2D& p2, const SimplePoint2D& p3);
bool areCollinear(const SimplePoint2D& p1, const SimplePoint2D& p2, const SimplePoint2D& p3);

double getTime();
vector<SimplePoint2D> randomVectorSimplePoint2D(long count, int minX, int maxX, int minY, int maxY);
