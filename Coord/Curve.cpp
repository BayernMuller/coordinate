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
	vector<Point> dots;
	CPoint o = rect.CenterPoint();
	o.Offset(m_nDx, m_nDy);
	int firstDx, lastDx;
	for (int i = -o.x + m_nDx, dy; i <= o.x - m_nDx; i++)
	{
		dy = f(i);
		if (0 <= o.y - dy && o.y - dy <= rect.bottom)
			dots.push_back(Point(i + o.x, o.y - dy));
	}
	if (!dots.empty())
	{
		firstDx = dots.begin()->X - o.x - 1;
		lastDx = (--dots.end())->X - o.x + 1;
		dots.insert(dots.begin(), Point(firstDx + o.x, o.y - f(firstDx)));
		dots.push_back(Point(lastDx + o.x, o.y - f(lastDx)));
	}
	G.DrawLines(&Pen(m_Color, REAL(m_nThick)), dots.data(), dots.size());
}
