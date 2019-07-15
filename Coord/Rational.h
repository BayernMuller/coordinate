#pragma once
#include "Curve.h"
class CRational : public CCurve
{
public:
	CRational();
	~CRational();

private:
	int f(int x);
};

