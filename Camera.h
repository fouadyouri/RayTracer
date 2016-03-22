#pragma once
#include "Vect3d.h"

class Camera {

public:

	vect3d camDown;
	vect3d camRight;
	vect3d origin;
	vect3d lookAt;

	
	Camera(vect3d camD, vect3d camR, vect3d orig, vect3d lookA) {
		camDown = camD;
		camRight = camR;
		origin = orig;
		lookAt = lookA;
	}
	
	
	vect3d getCamUp(vect3d position);
	vect3d getCamDown(vect3d position);
	vect3d getCamRight(vect3d position);
	vect3d getCamLeft(vect3d position);
	


};
