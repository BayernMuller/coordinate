#pragma once
#include "Curve.h"
class CRational : public CCurve
{
public:
	CRational();
	~CRational();
	//void Draw(Graphics& G, CRect& rect);

private:
	int f(int x);
};

