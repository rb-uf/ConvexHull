
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

vector<SimplePoint2D> test2 {
	PT(2, 3),
	PT(4, 1),
	PT(6, 2),
	PT(5, 3),
	PT(5, 4),
	PT(4, 3),
	PT(3, 2),
	PT(3, 3),
	PT(1, 2),
	PT(3, 4)
};
