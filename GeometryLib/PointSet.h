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
	CUBE,
	SQUAREAA
};

class PointSet
{
public:
	PointSet(void);
	virtual ~PointSet(void);

	virtual PSType type() const = 0;
private:
};
