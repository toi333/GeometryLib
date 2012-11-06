#pragma once

#include "GeometryLib.h"

class Camera
{
public:
	Vector p, dir;
	double pitch;
	double yaw;

	void transform(void) const;

	void update(double t);
	void rotate(int x, int y);
	void move(const Vector &_dir);

	Vector getCameraDirection(void) const;
private:
};
