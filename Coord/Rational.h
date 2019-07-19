#pragma once
#include "Curve.h"
class CRational : public CCurve
{
public:
	CRational();
	~CRational();
	void Selialize(CArchive& ar, Child kind = null);
	CString GetString();
private:
	int f(int x);
};

