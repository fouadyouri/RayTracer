#pragma once

#include "Ray.h"
#include "Color.h"

class Object {

public:

	virtual double findIntersectionAt(Ray r) = 0;

	virtual Color getColor() = 0;

};
