#pragma once


class Color {
	double red;   
	double green;
	double blue;

public:
// ===== Constructer =====
	Color() {
		red = 0;
		green = 0;
		blue = 0;
	}

// ====== Constructer with parameter ======
	Color(double r, double g, double b) {
		red = r;
		green = g;
		blue = b;
	}



	double getColorRed();
	double getColorGreen();
	double getColorBlue();

	void setColorRed(double r);
	void setColorGreen(double g);
	void setColorBlue(double b);

};

