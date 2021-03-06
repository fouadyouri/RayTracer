#pragma once

#include "Object.h"
#include <math.h>

double fmin2(double st_var1, double nd_var2) {
	if(st_var1 <= nd_var2)
		return st_var1;
	else
		return nd_var2;
}

class Sphere:public Object {
public:
	vect3d center;
	double radius;
	Color color;

	Sphere() {};
	~Sphere() {};

// ====== Constructor with variables ======
	Sphere(vect3d center_var, double radius_var) {
		center = center_var;
		radius = radius_var;
	}

// =========== Get Functions ===========
	vect3d getNormalAt(vect3d vect_arg) {
		vect3d n;
		vect3d PminC = vect_arg.vectAdd(center.negative());

		n = PminC.normalized();
		return n;
	}
    Color getColor() {
		return color;
	}
	double getRadius() {
		return radius;
	}
	vect3d getCenter() {
		return center;
	}
// =======================================

	double findIntersectionAt(Ray ray_arg) {
		//double a = 1.0;
		double b = 2 * (ray_arg.getOrigin().vectAdd(center.negative())).dotProduct(ray_arg.getDirection());
		vect3d PminO = ray_arg.getOrigin().vectAdd(center.negative());
		double c = PminO.dotProduct(PminO) - (radius * radius);

		double insideSqrt = b * b - 4 * c;

		if(insideSqrt < 0) {			// Return -1 because it's complex numbers
			return -1;					//---------------------------------------
		}								//---------------------------------------
		else if(insideSqrt > 0) {
			double T1 = -(b + sqrt(insideSqrt)) / 2;
			double T2 = -(b - sqrt(insideSqrt)) / 2;

			if (T1 < 0) {
				if (T2 < 0)         // Return -1 if T1 and T2 are negatives
					return -1;      //-------------------------------------
				else if (T2 >= 0)       // Return only T2 because T1 is negative
					return T2;          //--------------------------------------
			}
			else if (T1 >= 0) {
				if (T2 < 0)         // Return only T1 because T2 is negative
					return T1;      //--------------------------------------
				else if (T2 >= 0)           // Return The shortest distance between T1 and T2
					return fmin2(T1, T2);   //-----------------------------------------------
			}
		}
		else {
			double T = - b / 2;
			return T;
		}
	}
};


