lc = 0.03;

Point(5) = {0.5, 0.5, 0, lc};  // centar kruĹľnice
Point(1) = {0.5, 0.0, 0, lc};
Point(2) = {1.0, 0.5, 0, lc};
Point(3) = {0.5, 1.0, 0, lc};
Point(4) = {0.0, 0.5, 0, lc};

Circle(1) = {1, 5, 2};
Circle(2) = {2, 5, 3};
Circle(3) = {3, 5, 4};
Circle(4) = {4, 5, 1};

// Granica domene 
Line Loop(1) = {1, 2, 3, 4};

// Ravninska domena. Prvo vanjski rub, zatim rub rupe.
Plane Surface(1) = {1};
