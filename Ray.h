 #pragma once

#include "Vect3d.h"

class Ray {
	vect3d origin;
	vect3d direction;

public:

// ===== Constructor =====
	Ray() {

		origin.x = 0;
		origin.y = 0;
		origin.z = 0;

		direction.x = 0;
		direction.y = 0;
		direction.z = 1;
	}

// ====== Constructor with parameters ======
	Ray(vect3d newOrigin, vect3d newDirection) {

		origin.x = newOrigin.x;
		origin.y = newOrigin.y;
		origin.z = newOrigin.z;

		direction.x = newDirection.x;
		direction.y = newDirection.y;
		direction.z = newDirection.z;
	}

	void setOrigin(vect3d newOrigin);

	void setDirection(vect3d newDirection);

	vect3d getOrigin();

	vect3d getDirection();

};
