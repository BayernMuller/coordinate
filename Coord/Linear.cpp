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

bool CLinear::IsSelected(CPoint & pt, CPoint & center)
{
	int b = m_Coeff[1] * 2 * m_nRatio;
	center.Offset(m_nDx, m_nDy);
	return abs(center.y - (f(pt.x - center.x)) - b - pt.y) < 10;
}

void CLinear::Selialize(CArchive & ar, Child kind)
{
	CGraph::Selialize(ar, line);
}

int CLinear::f(int x)
{
	return (int)round((m_Coeff[0] * (double(x) / m_nRatio) - m_Coeff[1]) * m_nRatio);
}

