#include "stdafx.h"
#include "Rational.h"


CRational::CRational()
{
}


CRational::~CRational()
{
}
/*
void CRational::Draw(Graphics & G, CRect & rect)
{
	int nHalf = rect.Width() / 2;
	bool bDraw = false;
	vector<Point> dots;
	CPoint o = rect.CenterPoint();
	o.Offset(m_nDx, m_nDy);
	for (int i = -nHalf - m_nDx, dy; i <= nHalf - m_nDx; i++)
	{
		dy = f(i);
		if (rect.PtInRect({ i + o.x, o.y - dy }))
		{
			if (!bDraw)
				dots.push_back(Point(i + o.x - 1, o.y - f(i - 1)));
			dots.push_back(Point(i + o.x, o.y - dy));
			bDraw = true;
		}
		else if (bDraw)
		{
			dots.push_back(Point(i + o.x, o.y - dy));
			G.DrawLines(&Pen(m_Color, REAL(m_nThick)), dots.data(), dots.size());
			dots.clear();
			bDraw = false;
		}
	}
	G.DrawLines(&Pen(m_Color, REAL(m_nThick)), dots.data(), dots.size());
}*/

int CRational::f(int x)
{
	return (int)round((m_Coeff[0] / (double(x) / m_nRatio - m_Coeff[1]) + m_Coeff[2]) * m_nRatio);
}
