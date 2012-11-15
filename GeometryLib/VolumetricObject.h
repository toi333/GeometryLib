#pragma once

#include "PointSet.h"
#include "Ray.h"

class VolumetricObject :
	public PointSet
{
public:
	VolumetricObject(void);
	virtual ~VolumetricObject(void);

	virtual Vector pos() const = 0;
	virtual double volume() const = 0;
	virtual std::pair<double, Vector> reflect(const Ray &r) const = 0;
};

