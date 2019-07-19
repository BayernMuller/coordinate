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
	int radius = (int)round(pow(m_Coeff[2], .5) * m_nRatio);
	int dx = (int)round(m_Coeff[0] * m_nRatio), dy = (int)round(m_Coeff[1] * m_nRatio);
	auto o = rect.CenterPoint();
	o.Offset(m_nDx + dx, m_nDy - dy);
	Rect ellipse(o.x - radius, o.y - radius, radius * 2, radius * 2);
	G.DrawEllipse(&Pen(m_Color, REAL(m_nThick)), ellipse);
}

void CCircle::Selialize(CArchive & ar, Child kind)
{
	CGraph::Selialize(ar, circle);
}

bool CCircle::IsSelected(CPoint & pt, CPoint & center)
{
	double dis, radius = sqrt(m_Coeff[2]) * m_nRatio;
	int dx = (int)round(m_Coeff[0] * m_nRatio), dy = (int)round(m_Coeff[1] * m_nRatio);
	center.Offset(m_nDx + dx, m_nDy - dy);
	dis = sqrt(pow(center.x - pt.x, 2) + pow(center.y - pt.y, 2));
	return abs(dis - radius) < 10;
}

CString CCircle::GetString()
{
	int s, m;
	CString str, temp[3];
	for (int i = 0; i < 3; i++)
	{
		CString format = _T("%d");
		m = m_Coeff[i].GetMom(), s = m_Coeff[i].GetSon();
		if (i != 2)
			format.Insert(1, _T('+'));
		if (m_Coeff[i].GetMom() != 1)
			format.Append(_T("/%d"));
		temp[i].Format(format, s * ((i != 2) ? -1 : 1), m);
	}
	str.Format(_T("(x%s)^2 + (y%s)^2 = %s"), temp[0], temp[1], temp[2]);
	return str;
}
