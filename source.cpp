#include <iostream>
#include "Color.h"

using namespace std;

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

	int width = 1920;
	int height = 1080;
	int dpi = 72;

	Color* picture = new Color[width * height];
	double h1 = (height / 100.0) * 30;
	double h2 = (height / 100.0) * 90;
	double v1 = (width / 100.0) * 23;
	double v2 = (width / 100.0) * 77;

	double r = 100.0;
	double m = 150.0;
	double n = 180.0;
	double val = 0;

	// ================== la methode de dessin ====================
	for(int x = 0; x < width; x++) {
		for(int y = 0; y < height; y++) {
			int thisOne = y * width + x;
			double a = x - m;
			double b = y - n;

		// ================== Circle ====================
			
			if( a != 0) {
				val = (((r * r) - (b * b)) / (a * a));
				val -= 1.0;
			} 
			else {
				val = 0;
			}
			if(-0.1 < val < 0.1) {
				picture[thisOne] = Color(0, 0, 0);
			}
			else {
				picture[thisOne] = Color(1, 1, 1);
			}

		// ============== horizontal line ================
			if(y == h1 || y == h2) {
				picture[thisOne] = Color(1, 0, 0);
			}
		
		// ============== Vertical line ================	
			if(x == v1 || x == v2) {
				picture[thisOne] = Color(1, 0, 0);
			}
		// ============== Diagonale line ================
			if(x - y == 0) {
				picture[thisOne] = Color(1, 1, 1);
			}
		
			
		}
	}


	saveBMP("test.bmp", width, height, dpi, picture);

	delete picture;

	return 0;
}
