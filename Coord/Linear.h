#pragma once
#include "Graph.h"

class CLinear : public CGraph
{
public:
	CLinear();
	~CLinear();
	
	void Draw(Graphics& G, CRect & rect);
	void SetFunction(Terms args);
	bool IsSelected(CPoint& pt, CPoint& center);

private:
	
};

