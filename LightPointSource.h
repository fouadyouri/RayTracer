#pragma once

#include "LightSource.h"

class LightSourcePoint:public LightSource {
public:
	vect3d position;
	Color color;

	vect3d getLightPosition();
	Color getLightColor();
};

vect3d LightSourcePoint::getLightPosition() {
	return position;
}

Color LightSourcePoint::getLightColor() {
	return color;
}
