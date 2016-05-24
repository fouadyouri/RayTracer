#pragma once

class vect3d {
public:
	double x;
	double y;
	double z;

// ===== Constructor =====
	vect3d() {
		x = 0;
		y = 0;
		z = 0;
	}

// ====== Constructor with parameters ======
	vect3d(double x_var, double y_var, double z_var) {
		x = x_var;
		y = y_var;
		z = z_var;
	}

	double dotProduct(vect3d v);
	double abs();

	vect3d vectAdd(vect3d v);
	vect3d vectMulti(double s);
	vect3d normalized();
	vect3d negative();
	vect3d crossProduct(vect3d v);

};
