#pragma once

#include "GeometryLib.h"

class Camera
{
public:
	void transform(void);

	void update(double t);
	void rotate(int x, int y);
	void move(const Vector &_dir);

	Vector p, dir;
	double pitch;
	double yaw;
private:
};
