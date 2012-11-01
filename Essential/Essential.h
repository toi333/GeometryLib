#pragma once

#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <cmath>
#include "math.h"
#include <algorithm>

const double EPS = 10e-7;

//double abs(double x);
double sgn(double x);

double min(double x, double y);
double max(double x, double y);
double min(double x, double y, double z);
double max(double x, double y, double z);