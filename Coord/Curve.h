#pragma once
#include "Graph.h"
class CCurve : public CGraph
{
public:
	CCurve();
	~CCurve();

	virtual void Draw(Graphics& G, CRect& rect);
	void Selialize(CArchive& ar, Child kind = null);
	
private:

};

