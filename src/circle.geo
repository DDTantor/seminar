lc = 0.03;

Point(9) = {0.5, 0.5, 0, lc};  // centar kruĹľnice
Point(5) = {0.5, 0.0, 0, lc};
Point(6) = {1.0, 0.5, 0, lc};
Point(7) = {0.5, 1.0, 0, lc};
Point(8) = {0.0, 0.5, 0, lc};

Circle(5) = {5, 9, 6};
Circle(6) = {6, 9, 7};
Circle(7) = {7, 9, 8};
Circle(8) = {8, 9, 5};

// Granica domene 
Line Loop(2) = {5,6,7,8};

// Ravninska domena. Prvo vanjski rub, zatim rub rupe.
Plane Surface(1) = {2} ;
