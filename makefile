all:
	g++ -Wzero-as-null-pointer-constant -c -I ../GeometricDataStructures2D \
		ConvexHullGrahamScan.cpp \
		ConvexHullJarvisMarch.cpp \
		ConvexHullMonotoneChain.cpp \
		ConvexHullDivideandConquer.cpp \
		Utilities.cpp \
		main.cpp
	g++ ConvexHullGrahamScan.o \
		ConvexHullJarvisMarch.o \
		ConvexHullMonotoneChain.o \
		ConvexHullDivideandConquer.o \
		Utilities.o \
		main.o \
		../GeometricDataStructures2D/libGeometricDataStructures2D.a \
		-lgmp -lgmpxx \
		-o test
