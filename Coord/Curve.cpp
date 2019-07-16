#include "stdafx.h"
#include "Curve.h"
#include <vector>
using namespace std;

CCurve::CCurve()
{
}


CCurve::~CCurve()
{
}


void CCurve::Draw(Graphics & G, CRect & rect)
{
	const int nHalf = rect.Width() / 2;
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
	if (!dots.empty())
		G.DrawLines(&Pen(m_Color, REAL(m_nThick)), dots.data(), dots.size());
}

void CCurve::Selialize(CArchive & ar, Child kind)
{
	CGraph::Selialize(ar, curve);
}
