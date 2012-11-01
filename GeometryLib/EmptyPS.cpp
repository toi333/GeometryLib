#include "StdAfx.h"
#include "EmptyPS.h"

EmptyPS::EmptyPS(void)
{
}

EmptyPS::~EmptyPS(void)
{
}

PSType EmptyPS::type()
{
	return EMPTYPS;
}