#include "Vect3d.h"
#include <math.h>


vect3d vect3d::vectAdd(vect3d v) {
	
	vect3d newVect;

	newVect.x = x + v.x;
	newVect.y = y + v.y;
	newVect.z = z + v.z;

	return newVect;
}

vect3d vect3d::vectMulti(double s) {
	
	vect3d newVect;
	
	newVect.x = x * s;
	newVect.y = y * s;
	newVect.z = z * s;

	return newVect;
}

double vect3d::dotProduct(vect3d v) {

	double dotProdResult = (x * v.x) + (y * v.y) + (z * v.z);

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

vect3d vect3d::crossProduct(vect3d v) {

	vect3d newVect;
	
	newVect.x = (y * v.z) - (z * v.y);
	newVect.y = (z * v.x) - (x * v.z);
	newVect.z = (x * v.y) - (y * v.x);

	return newVect;
} 
