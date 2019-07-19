#pragma once
#include "Graph.h"
class CCircle : public CGraph
{
public:
	CCircle();
	~CCircle();
	void Draw(Graphics &G, CRect &rect);
	void Selialize(CArchive& ar, Child kind = null);
	bool IsSelected(CPoint& pt, CPoint& center);

	CString GetString();
private:

};