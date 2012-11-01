#pragma once

#include "GeometryLib.h"

class Camera
{
public:
	void transform(void) const;

	void update(double t);
	void rotate(int x, int y);
	void move(const Vector &_dir);

	Vector getCameraDirection(void) const;

	Vector p, dir;
	double pitch;
	double yaw;
private:
};
