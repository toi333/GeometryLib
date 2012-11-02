#pragma once

#define _USE_MATH_DEFINES
#include "stdafx.h"
#include <cmath>
#include "math.h"
#include <algorithm>
#include <limits>

const double EPS = 10e-7;
static double fjldskjflkdsjlfkjldjlkjfldsjl = 0.;
const double INF = 1. / fjldskjflkdsjlfkjldjlkjfldsjl;

//double abs(double x);
double sgn(double x);

double min(double x, double y);
double max(double x, double y);
double min(double x, double y, double z);
double max(double x, double y, double z);