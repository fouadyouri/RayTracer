#include "Vect3d.h"
#include <math.h>


vect3d vect3d::vectAdd(vect3d vect_arg) {
	
	vect3d newVect;

	newVect.x = x + vect_arg.x;
	newVect.y = y + vect_arg.y;
	newVect.z = z + vect_arg.z;

	return newVect;
}

vect3d vect3d::vectMulti(double point_arg) {
	
	vect3d newVect;
	
	newVect.x = x * point_arg;
	newVect.y = y * point_arg;
	newVect.z = z * point_arg;

	return newVect;
}

double vect3d::dotProduct(vect3d vect_arg) {

	double dotProdResult = (x * vect_arg.x) + (y * vect_arg.y) + (z * vect_arg.z);

	return dotProdResult;
}

double vect3d::abs() {

	double absResult = sqrt((x*x) + (y*y) + (z*z));
	
	return absResult;
}

vect3d vect3d::normalized() {
	
	vect3d newVect;
	
	newVect.x = x / abs();
	newVect.y = y / abs();
	newVect.z = z / abs();

	return newVect;
}

vect3d vect3d::negative() {
	
	vect3d newVect;
	
	newVect.x = -x;
	newVect.y = -y;
	newVect.z = -z;

	return newVect;
}

vect3d vect3d::crossProduct(vect3d vect_arg) {

	vect3d newVect;
	
	newVect.x = (y * vect_arg.z) - (z * vect_arg.y);
	newVect.y = (z * vect_arg.x) - (x * vect_arg.z);
	newVect.z = (x * vect_arg.y) - (y * vect_arg.x);

	return newVect;
} 
