#pragma once

#include "Object.h"

class Plane:public Object {
public:
	double distance;
	vect3d normal;
	Color color;

	Plane() {};
	~Plane() {};

	Plane(vect3d nor_arg, double dist_arg) {
		distance = dist_arg;
		normal = nor_arg;
	}

	vect3d getNormalAt(vect3d vect_arg) {
		return normal;
	}

	double findIntersectionAt(Ray ray_arg) {
		if (normal.dotProduct(ray_arg.getDirection()) == 0)
			return -1;
		else {
			double t = -1.0 * (normal.dotProduct(ray_arg.getOrigin()) + distance) / (normal.dotProduct(ray_arg.getDirection()));
			return t;
		}
	}

	Color getColor() {
		return color;
	}

	vect3d getNormal() {
		return normal;
	}

	double getDistance() {
		return distance;
	}

};
