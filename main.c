#include <locale.h>
#include <stdlib.h>
#include <math.h>

#include "graph.h"

double weierstrass(double x) {
	double s = 0;
	double a = 0.5;
	double b = 15;
	for (int n = 0; n < 100; n++) {
		s += pow(a, n) * cos(pow(b, n) * M_PI * x);
	}
	return s;
}

double circle(double x, double y, double r) {
	return abs(x*x+y*y - r*r) < r;
}

int main(void) {
	double scale = 50;
	setlocale(LC_ALL, "");
	GRAPH(1, circle(x, y, 10) || circle(x, y, 20) || circle(x, y, 50));
	return 0;
}
