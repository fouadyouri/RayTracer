#include <iostream>
#include <stdio.h>
#include <vector>

#include "Color.h"
#include "Vect3d.h"
#include "Camera.h"
#include "Object.h"
#include "Plane.h"
#include "Sphere.h"
#include "Ray.h"

using namespace std;

int find(vector<double> a){
	double max, min;
	int index;
	if (a.size() == 0)
		return -1;
	else{
		max = a[0];
		index = 0;
		for (int i = 1; i<a.size(); i++){
			if (a[i] > max)
			{
				max = a[i];
				index = i;
			}
		}
		if (max<0)
			return -1;
		min = max;
		for (int i = 1; i<a.size(); i++){
			if ((a[i] < min) && (a[i] > 0))
			{
				min = a[i];
				index = i;
			}
		}
		return index;
	}
}

void saveBMP(const char *fileName, int width, int height, int dpi, Color *data) {

	FILE *f;
	int k = width * height;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = int(factor);
	int ppm = dpi * m;
	unsigned char bmpFileHeader[14] = {'B', 'M', 0,0,0,0, 0,0,0,0, 54,0,0,0};
	unsigned char bmpInfoHeader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0,24,0};

	bmpFileHeader[2] = (unsigned char)(filesize);
	bmpFileHeader[3] = (unsigned char)(filesize>>8);
	bmpFileHeader[4] = (unsigned char)(filesize>>16);
	bmpFileHeader[5] = (unsigned char)(filesize>>24);

	bmpInfoHeader[4] = (unsigned char)(width);
	bmpInfoHeader[5] = (unsigned char)(width>>8);
	bmpInfoHeader[6] = (unsigned char)(width>>16);
	bmpInfoHeader[7] = (unsigned char)(width>>24);

	bmpInfoHeader[8] = (unsigned char)(height);
	bmpInfoHeader[9] = (unsigned char)(height>>8);
	bmpInfoHeader[10] = (unsigned char)(height>>16);
	bmpInfoHeader[11] = (unsigned char)(height>>24);

	bmpInfoHeader[21] = (unsigned char)(s);
	bmpInfoHeader[22] = (unsigned char)(s>>8);
	bmpInfoHeader[23] = (unsigned char)(s>>16);
	bmpInfoHeader[24] = (unsigned char)(s>>24);

	bmpInfoHeader[25] = (unsigned char)(ppm);
	bmpInfoHeader[26] = (unsigned char)(ppm>>8);
	bmpInfoHeader[27] = (unsigned char)(ppm>>16);
	bmpInfoHeader[28] = (unsigned char)(ppm>>24);

	bmpInfoHeader[29] = (unsigned char)(ppm);
	bmpInfoHeader[30] = (unsigned char)(ppm>>8);
	bmpInfoHeader[31] = (unsigned char)(ppm>>16);
	bmpInfoHeader[32] = (unsigned char)(ppm>>24);

	f = fopen(fileName, "wb");
	fwrite(bmpFileHeader, 1, 14, f);
	fwrite(bmpInfoHeader, 1, 40, f);

	for(int i = 0; i < k; i++) {

		double red = data[i].getColorRed() * 255;
		double green = data[i].getColorGreen() * 255;
		double blue = data[i].getColorBlue() * 255;

		unsigned char color[3] = {(int)blue, (int)green, (int)red};
		fwrite(color, 1, 3, f);
	}
}

void drawLine(Color *picture, int  width, int height, int x1, int y1, int x2, int y2) {
	double k = (y2 - y1) / (x2 - x1);
	for (int x = x1; x < x2; x++) {
		double y = k * x;

		int thisOne = y * width + x;
		picture[thisOne] = Color(1, 0, 0);
	}
}

int main (int argc, char* argv[]) {

	int width = 1000;
	int height = 1000;
	int dpi = 72;

	Color* picture = new Color[width * height];

	vect3d X(1, 0, 0);
	vect3d Y(0, 1, 0);
	vect3d Z(0, 0, 1);
	vect3d O(0, 0, 0);

	vect3d camPosition = O;
	vect3d camDirection = Y;
	vect3d camRight = X;
	vect3d camUp = Z;
	Color red(1, 0, 0);
	Color green(0, 1, 0);

	Camera camera(camUp, camRight, camPosition, camDirection);

	vect3d normalPlane_1 = Y.negative();
	double distancePlane_1 = 20;
	Plane plane_1(normalPlane_1, distancePlane_1);
	plane_1.color = red;

	vect3d centerSphere_1(-2, 10, 0);
	double radiusSphere_1 = 0.5;
	Sphere sphere_1(centerSphere_1, radiusSphere_1);
	sphere_1.color = green;

	vector<Object*> v;
	v.push_back(dynamic_cast<Object*>(&plane_1));
	v.push_back(dynamic_cast<Object*>(&sphere_1));

	for (int i = 0; i < width; i++) {
		for (int j = 0; j < height; j++) {
			int thisone = i * width + j;
			double xR = static_cast<float>(i) / width;
			double yR = static_cast<float>(j) / height;

			vect3d ray_origin = camera.getPosition();
			vect3d ray_direction = camera.getCamDirection().vectAdd(camera.getCamRight().vectMulti(xR - 0.5).vectAdd(camera.getCamUp().vectMulti(yR - 0.5))).normalized();

			Ray r(ray_origin, ray_direction);
			vector<double> intersections;
			for (int k = 0; k < v.size(); k++) {
				intersections.push_back(v[k]->findIntersectionAt(r));
			}
			int indxClosestObject = find(intersections);
			if (indxClosestObject == -1) {
				picture[thisone].setColorBlue(0);
				picture[thisone].setColorGreen(0);
				picture[thisone].setColorRed(0);
			}
			else {
				picture[thisone].setColorBlue(v[indxClosestObject]->getColor().getColorBlue());
				picture[thisone].setColorGreen(v[indxClosestObject]->getColor().getColorGreen());
				picture[thisone].setColorRed(v[indxClosestObject]->getColor().getColorRed());
			}

		}

	}


	saveBMP("test.bmp", width, height, dpi, picture);

	delete picture;

	return 0;
}
