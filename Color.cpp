#include "Color.h"


// ======== Return RGB Colors ========
double Color::getColorRed() {
	return red;
}

double Color::getColorGreen() {
	return green;
}

double Color::getColorBlue() {
	return blue;
}

double Color::getColorSpecial(){
    return special;
}

// ========== Set RGB Colors ==========
void Color::setColorRed(double r) {
	red = r;
}

void Color::setColorGreen(double g) {
	green = g;
}

void Color::setColorBlue(double b) {
	blue = b;
}

void Color::setColorSpecial(double s){
    special = s;
}

Color Color::colorAdd(Color color_var) {
    color_var.red += red;
    color_var.green += green;
    color_var.blue += blue;

    return color_var;
}

Color Color::colorMultiColor(Color color_var) {
    color_var.red *= red;
    color_var.green *= green;
    color_var.blue *= blue;

    return color_var;
}

Color Color::colorMultiDouble(double var) {
    Color color_var;
    color_var.red = red;
    color_var.green = green;
    color_var.blue = blue;

    color_var.red *= var;
    color_var.green *= var;
    color_var.blue *= var;

    return color_var;
}

Color Color::normalized(){
    double sum = red+green+blue;
    double diff = sum - 3;
    if(diff > 0){
        red = red + diff*(red/sum);
        green = green + diff*(green/sum);
        blue = blue + diff*(blue/sum);
    }
    if(red > 1)
        red = 1;
    if(green > 1)
        green = 1;
    if(blue > 1)
        blue = 1;

    if(red < 0)
        red = 0;
    if(green < 0)
        green = 0;
    if(blue < 0)
        blue = 0;
    return *this;
}


