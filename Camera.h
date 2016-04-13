#pragma once
#include "Vect3d.h"

class Camera {

public:
	vect3d camUp;
	vect3d camRight;
	vect3d camPosition;
	vect3d camDirection;
	
	Camera(vect3d cUp_var, vect3d cRight_var, vect3d cPosition_var, vect3d cDirection_var) {
		camUp = cUp_var;
		camRight = cRight_var;
		camPosition = cPosition_var;
		camDirection = cDirection_var;
	}
	
	void setCamUp(vect3d position_var) {
		camUp = position_var;
	}
	void setCamDirection(vect3d position_var) {
		camDirection = position_var;
	}
	void setCamRight(vect3d position_var) {
		camRight = position_var;
	}
	void setCamPosition(vect3d position_var) {
		camPosition = position_var;
	}
	
	vect3d getCamUp() {
		return camUp;
	}
	vect3d getCamRight() {
		return camRight;
	}
	vect3d getPosition() {
		return camPosition;
	}
	vect3d getCamDirection() {
		return camDirection;
	}
};
