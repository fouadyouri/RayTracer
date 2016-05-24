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
#include "LightPointSource.h"

using namespace std;

int find(vector<double> a){
	double max, min;
	int index;
	if (a.size() == 0)
		return -1;
	else{
		max = a[0];
		index = 0;
		for (int i = 1; i < a.size(); i++){
			if (a[i] > max){
				max = a[i];
				index = i;
			}
		}
		if (max < 0)
			return -1;
		min = max;
		for (int i = 1; i < a.size(); i++){
			if ((a[i] < min) && (a[i] > 0)){
				min = a[i];
				index = i;
			}
		}
		return index;
	}
}
int find2( vector<double> a, int ind){
	double max,min;
	int index;
	if (a.size() == 0)
		return -1;
	else{
		max = a[0];
		index = 0;
		for (size_t i=1; i<a.size(); i++){
			if (a[i] > max && i != ind)
			{
				max = a[i];
				index = i;
			}
		}
		if (max<=0.0001)
			return -1;
		min = max;
		for (size_t i=1; i<a.size(); i++){
			if ((a[i] < min) && (a[i] > 0) &&(i != ind))
			{
				min = a[i];
				index = i;
			}
		}
		return index;
	}
}
int findByIndex(vector<double> a, int ind) {
    double min, max;
    int index;
    if (a.size() == 0)
        return -1;
    else{
        max = a[0];
        index = 0;
        for(int i = 1; i < a.size(); i++){
            if((a[i] > max) && (i != ind)){
                max = a[i];
                index = i;
            }
        }
        if (max <= 0.0001)
            return -1;
        min = max;
        for(int i = 1; i < a.size(); i++){
            if((a[i] < min) && (a[i] > 0) && (i != ind)){
                min = a[i];
                index = i;
            }
        }
        return index;
    }
}

Color getColorWithShadows(vect3d interPos, vect3d interRayDirec, vector<Object*> &scene, int indxClosestObj, LightSourcePoint light){
    double ambientLight = 0.7;
    Color finalColor = scene[indxClosestObj]->getColor();
    finalColor.colorMultiDouble(ambientLight);


    vect3d closestObjNormal = scene[indxClosestObj]->getNormalAt(interPos);

    bool shadowed = false;

    if(finalColor.getColorSpecial() <= 1.0 && finalColor.getColorSpecial() > 0.0){
        vect3d reflectDirection = (interRayDirec.negative().vectAdd(closestObjNormal.vectMulti(interRayDirec.negative().dotProduct(closestObjNormal)).vectAdd(interRayDirec).vectMulti(2.0))).normalized();
        Ray reflection(interPos, reflectDirection);
        //Ray ray;
        //vect3d insideBrackets = closestObjNormal.vectMulti(interRayDirec.negative().dotProduct(closestObjNormal)).vectAdd(interRayDirec);
        //ray.direction = (interRayDirec.negative().vectAdd(insideBrackets.vectMulti(2.0))).normalized();
        //ray.origin = interPos;

        	vector<double> intersections;
			for (int k = 0; k < scene.size(); k++){
				intersections.push_back(scene[k]->findIntersectionAt(reflection));
			}
			int indxClosestObject2 = find2(intersections, indxClosestObj);
			if (indxClosestObject2 != -1){

			    vect3d initialPosition = interPos.vectAdd(reflectDirection.vectMulti(intersections[indxClosestObject2]));
                Color reflectionColor = getColorWithShadows(initialPosition, reflectDirection, scene, indxClosestObject2, light);

                finalColor = finalColor.colorAdd(reflectionColor.colorMultiDouble(scene[indxClosestObj]->getColor().getColorSpecial()));

			}

    }

    vect3d lightDirection = (light.getLightPosition().vectAdd( interPos.negative() )).normalized();

    double cos = lightDirection.dotProduct(closestObjNormal);
    if(cos > 0){
        double distToLight = (light.getLightPosition().vectAdd(interPos.negative())).abs();

        Ray shadowRay(interPos, lightDirection);

        for(int i = 0; i < scene.size(); i++){
            if(distToLight > scene[i]->findIntersectionAt(shadowRay) && i != indxClosestObj)
                shadowed = true;
        }
    }

    if(shadowed == false)
    {
        Color step2 = scene[indxClosestObj]->getColor();
        Color step3 = light.getLightColor();
        Color step4 = step2.colorMultiColor(step3);
        Color step1 = step4.colorMultiDouble(cos);
        finalColor = finalColor.colorAdd(step1);
    }
        //finalColor = finalColor.colorAdd(scene[indxClosestObj]->getColor().colorMultiColor(light.getLightColor()).colorMultiDouble(cos));

    return finalColor.normalized();
}

void saveBMP(const char *fileName, int width, int height, int dpi, Color *data){

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

	for(int i = 0; i < k; i++){
		double red = data[i].getColorRed() * 255;
		double green = data[i].getColorGreen() * 255;
		double blue = data[i].getColorBlue() * 255;

		unsigned char color[3] = {(int)blue, (int)green, (int)red};
		fwrite(color, 1, 3, f);
	}
}

void drawLine(Color *picture, int  width, int height, int x1, int y1, int x2, int y2){
	double k = (y2 - y1) / (x2 - x1);
	for (int x = x1; x < x2; x++){
		double y = k * x;

		int thisOne = y * width + x;
		picture[thisOne] = Color(1, 0, 0, 0);
	}
}

int main (int argc, char* argv[]){

	int width = 3000;
	int height = 3000;
	int dpi = 72;

	Color* picture = new Color[width * height];

	vect3d X(1, 0, 0);
	vect3d Y(0, 1, 0);
	vect3d Z(0, 0, 1);
	vect3d O(0, 0, 0);

    LightSourcePoint light;
    light.color = Color(1, 1, 1, 0);
    light.position = vect3d(100, 100, 100);

	vect3d camPosition = O;
	vect3d camDirection = Y;
	vect3d camRight = X;
	vect3d camUp = Z;

	Color red(1, 0, 0, 0);
	Color green(0, 1, 0, 0);
	Color blue(0, 0, 1, 0.9);

	Camera camera(camUp, camRight, camPosition, camDirection);


	vect3d normalPlane_1 = Y;
	double distancePlane_1 = -10;
	Plane plane_1(normalPlane_1, distancePlane_1);
	Color colorPlane_1(0.5, 0.5, 0.5, 1.0);
	plane_1.color = colorPlane_1;

    vect3d normalPlane_2 = X;
	double distancePlane_2 = 0;
	Plane plane_2(normalPlane_2, distancePlane_2);
	Color colorPlane_2(0, 0, 0.37, 0);
	plane_2.color = colorPlane_2;

//---------------- Spheres ----------------
	vect3d centerSphere_1(-2, 10, 0);
	double radiusSphere_1 = 0.5;
	Color colorSphere_1(0, 0.7, 0, 1.0);
    Sphere sphere_1(centerSphere_1, radiusSphere_1);
	sphere_1.color = colorSphere_1;

	vect3d centerSphere_2(4, 15, 6);
	double radiusSphere_2 = 0.8;
    Color colorSphere_2(0, 0, 1, 0.9);
    Sphere sphere_2(centerSphere_2, radiusSphere_2);
	sphere_2.color = colorSphere_2;

	vect3d centerSphere_3(-1, 20, -2);
	double radiusSphere_3 = 0.9;
	Color colorSphere_3(0.9, 0.9, 0.9, 0.9);
    Sphere sphere_3(centerSphere_3, radiusSphere_3);
	sphere_3.color = colorSphere_3;

	vect3d centerSphere_4(2, 20, -8);
	double radiusSphere_4 = 1.0;
	Color colorSphere_4(0.6, 0.2, 0.7, 0.6);
    Sphere sphere_4(centerSphere_4, radiusSphere_4);
	sphere_4.color = colorSphere_4;

    vect3d centerSphere_5(8, 20, -4);
	double radiusSphere_5 = 2.0;
	Color colorSphere_5(0.4, 0.9, 0.5, 0.6);
    Sphere sphere_5(centerSphere_5, radiusSphere_5);
	sphere_5.color = colorSphere_5;





	vector<Object*> v;
	//v.push_back(dynamic_cast<Object*>(&plane_1));
	v.push_back(dynamic_cast<Object*>(&plane_2));
	v.push_back(dynamic_cast<Object*>(&sphere_1));
	v.push_back(dynamic_cast<Object*>(&sphere_2));
    v.push_back(dynamic_cast<Object*>(&sphere_3));
    v.push_back(dynamic_cast<Object*>(&sphere_4));
    v.push_back(dynamic_cast<Object*>(&sphere_5));

	for (int i = 0; i < width; i++){
		for (int j = 0; j < height; j++){
			int thisone = i * width + j;
			double xR = static_cast<float>(i) / width;
			double yR = static_cast<float>(j) / height;

			vect3d ray_origin = camera.getPosition();
			vect3d ray_direction = camera.getCamDirection().vectAdd(camera.getCamRight().vectMulti(xR - 0.5).vectAdd(camera.getCamUp().vectMulti(yR - 0.5))).normalized();

			Ray r(ray_origin, ray_direction);
			vector<double> intersections;
			for (int k = 0; k < v.size(); k++){
				intersections.push_back(v[k]->findIntersectionAt(r));
			}
			int indxClosestObject = find(intersections);
			if (indxClosestObject == -1){
				picture[thisone].setColorBlue(0);
				picture[thisone].setColorGreen(0);
				picture[thisone].setColorRed(0);
			}
			else {
                vect3d initialPosition = camera.getPosition().vectAdd(ray_direction.vectMulti(intersections[indxClosestObject]));
                Color finalColor = getColorWithShadows(initialPosition, ray_direction, v, indxClosestObject, light);

				picture[thisone].setColorBlue(finalColor.getColorBlue());
				picture[thisone].setColorGreen(finalColor.getColorGreen());
				picture[thisone].setColorRed(finalColor.getColorRed());
			}
		}
	}

	saveBMP("test.bmp", width, height, dpi, picture);

	delete picture;

	return 0;
}
