#include "Essential.h"

using namespace std;

int sgn(double x)
{
	return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

double min(double x, double y, double z)
{
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

double max(double x, double y, double z)
{
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}

bool isBetween(double x, double a, double b)
{
	return a <= x && x <= b;
}

double intervalIntersection(double a1, double a2, double b1, double b2)
{
	return max(min(a2, b2) - max(a1, b1), 0.0);
}

double intervalDistance(double a1, double a2, double b1, double b2)
{
	return max(a1, b1) - min(a2, b2);
}
