#include "stdafx.h"
#include "Essential.h"

//double abs(double x)
//{
//	return x < 0 ? -x : x;
//}

double sgn(double x)
{
	return abs(x) < EPS ? 0 : (x < 0 ? -1 : 1);
}

double min(double x, double y)
{
	return x < y ? x : y;
}

double max(double x, double y)
{
	return x > y ? x : y;
}

double min(double x, double y, double z)
{
	return x < y ? (x < z ? x : z) : (y < z ? y : z);
}

double max(double x, double y, double z)
{
	return x > y ? (x > z ? x : z) : (y > z ? y : z);
}