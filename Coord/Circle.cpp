#include "stdafx.h"
#include "Circle.h"


CCircle::CCircle()
{
}


CCircle::~CCircle()
{
}

void CCircle::Draw(Graphics & G, CRect & rect)
{
	// (x - m_Coeff[0])^2 + (y - m_Coeff[1])^2 = m_Coeff[2])
	auto radius = pow(m_Coeff[2], 0.5) * m_nRatio;
	auto o = rect.CenterPoint();
	o.Offset(m_nDx, m_nDy);
	int dx = m_Coeff[0] * m_nRatio, dy = m_Coeff[1] * m_nRatio;
	G.DrawEllipse(&Pen(m_Color, REAL(m_nThick)),
		Rect(o.x - radius + dx, o.y - radius + m_nDy + dy, radius * 2, radius * 2));
}
