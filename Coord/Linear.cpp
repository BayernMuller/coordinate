#include "stdafx.h"
#include "Linear.h"

CLinear::CLinear()
{
}


CLinear::~CLinear()
{
}

void CLinear::Draw(Graphics& G, CRect & rect)
{
	CPoint o = rect.CenterPoint();
	o.Offset(m_nDx, m_nDy);
	G.DrawLine(&Pen(m_Color, REAL(m_nThick)), 0, o.y + f(o.x), rect.right, o.y + f(o.x - rect.right));
}


void CLinear::SetFunction(Terms args)
{
	CGraph::SetFunction(args);
	(*(m_Coeff.end() - 1)) = (*(m_Coeff.end() - 1)).operator*(CFract(-1, 1));
}

bool CLinear::IsSelected(CPoint & pt, CPoint & center)
{
	int b = (int)round(*(m_Coeff.end() - 1)) * 2 * m_nRatio;
	center.Offset(m_nDx, m_nDy);
	return abs(center.y - (f(pt.x - center.x)) + b - pt.y) < 10;
}

