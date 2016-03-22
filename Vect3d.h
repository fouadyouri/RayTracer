#pragma once 

class vect3d {
public:
	double x;
	double y;
	double z;

// ===== Constructer =====
	vect3d() {
		x = 0;
		y = 0;
		z = 0;
	}

// ====== Constructer with parameters ======
	vect3d(double a, double b, double c) {
		x = a;
		y = b;
		z = c;
	}



	double dotProduct(vect3d v);
	double abs();

	vect3d vectAdd(vect3d v);
	vect3d vectMulti(double s);
	vect3d normalized();
	vect3d negative();
	vect3d crossProduct(vect3d v);

};
