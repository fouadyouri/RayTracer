#pragma once

class Color {
public:
	double red;
	double green;
	double blue;

	double special;

// ===== Constructor =====
	Color() {
		red = 0;
		green = 0;
		blue = 0;
		special = 0;
	}

// ====== Constructor with parameter ======
	Color(double r, double g, double b, double s) {
		red = r;
		green = g;
		blue = b;
		special = s;
	}

	double getColorRed();
	double getColorGreen();
	double getColorBlue();
    double getColorSpecial();

	void setColorRed(double r);
	void setColorGreen(double g);
	void setColorBlue(double b);
    void setColorSpecial(double s);

    Color colorAdd(Color color_var);
    Color colorMultiColor(Color color_var);
    Color colorMultiDouble(double var);
    Color normalized();

};

