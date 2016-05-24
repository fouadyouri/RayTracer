#pragma once

#include "Vect3d.h"
#include "Color.h"

class LightSource {
public:

	virtual vect3d getLightPosition() = 0;
	virtual Color getLightColor() = 0;

};


