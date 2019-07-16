#pragma once
#include "Graph.h"

class CLinear : public CGraph
{
public:
	CLinear();
	~CLinear();
	
	void Draw(Graphics& G, CRect & rect);
	bool IsSelected(CPoint& pt, CPoint& center);
	void Selialize(CArchive& ar, Child kind = null);

private:
	int f(int x);
};

