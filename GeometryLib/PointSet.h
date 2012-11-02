#pragma once

enum PSType
{
	VECTOR,
	LINE,
	RAY,
	SEGMENT,
	TRIANGLE,
	PLANE,
	EMPTYPS,
	POINTSET,
	CUBE
};

class PointSet
{
public:
	PointSet(void);
	~PointSet(void);

	virtual PSType type() const;
private:
};

