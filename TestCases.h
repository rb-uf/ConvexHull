
#include <vector>
#include "Number.h"
#include "SimplePoint2D.h"

#define PT(X, Y) SimplePoint2D(Number(#X), Number(#Y))

vector<SimplePoint2D> test1 {
	PT(0, 0),
	PT(2, 0),
	PT(2, 2),
	PT(0, 2),
	PT(1, 1)
};
