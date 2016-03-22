#pragma once

#include "Object.h"


class Plane:public Object {

	double d;
	vect3d direction;

	Plane(vect3d dir_arg, double d_arg) {

		d = d_arg;
		direction = dir_arg;

	}

	Plane() {};
	~Plane() {};
};
