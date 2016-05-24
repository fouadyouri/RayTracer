#include "Ray.h"


void Ray::setOrigin(vect3d newOrigin) {
	origin.x = newOrigin.x;
	origin.y = newOrigin.y;
	origin.z = newOrigin.z;
}

void Ray::setDirection(vect3d newDirection) {
	direction.x = newDirection.x;
	direction.y = newDirection.y;
	direction.z = newDirection.z;
}

vect3d Ray::getOrigin() {
	return origin;
}

vect3d Ray::getDirection() {
	return direction;
}

