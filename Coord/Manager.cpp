#include "stdafx.h"
#include "Manager.h"
#include "Linear.h"
#include "Curve.h"
#include "Circle.h"

CManager::CManager()
{
	auto *cur = new CCurve;
	cur->Initialize(Color(255, 0, 0), 3);
	cur->SetFunction(
		{
			{1 , 1},
			{0 , 1},
			{0 , 1},
			{0 , 1},
		});
	auto *line = new CLinear;
	line->Initialize(Color(0, 0, 0), 3);
	line->SetFunction(
		{
			{4 , 1},
			{10 , 1}
		});
	m_Funs.push_back(cur);
	m_Funs.push_back(line);

	/*
	auto *cir = new CCircle;
	cir->Initialize(Color(0, 0, 255), 1);
	cir->SetFunction(
		{
			{2},
			{4},
			{16}
		});
	m_Funs.push_back(cir);*/
}

CManager::~CManager()
{
	for (auto i : m_Funs)
		delete i;
}

void CManager::Draw(Graphics &G, CRect & rect)
{
	G.SetSmoothingMode(SmoothingModeAntiAlias);
	DrawCoordinate(G, rect);
	for (auto i : m_Funs)
		i->Draw(G, rect);
	m_Rect = rect;
}

void CManager::Select(UINT nFlag, CPoint& pt)
{
	for (auto i = m_Funs.begin(); i != m_Funs.end(); i++)
	{
		if ((*i)->IsSelected(pt, m_Rect.CenterPoint()))
		{
			if (nFlag != MK_CONTROL + MK_LBUTTON)
				m_Selee.clear();
			m_Selee.push_back(i);
			break;
		}
	}
}


void CManager::OnZoom(short zDelta)
{
	int ratio = CGraph::m_nRatio + (zDelta / 60);
	if (ratio < 30)
		return;
	CGraph::m_nRatio = ratio;
}

void CManager::OnScreenMove(int dx, int dy)
{
	CGraph::m_nDx -= dx;
	CGraph::m_nDy -= dy;
}

void CManager::Init()
{
	CGraph::m_nDx = CGraph::m_nDy = 0;
	CGraph::m_nRatio = 1;
}

void CManager::Delete()
{
	for (auto itr : m_Selee)
	{
		delete *itr;
		m_Funs.erase(itr);
	}
	m_Selee.clear();
}

void CManager::DrawCoordinate(Graphics & G, CRect & rect)
{
	Pen pen(Color(0, 0, 0), 1.0);
	CPoint pt = rect.CenterPoint();
	pt.Offset(CGraph::m_nDx, CGraph::m_nDy);
	G.DrawLine(&pen, 0, pt.y, rect.right, pt.y);
	G.DrawLine(&pen, pt.x, 0, pt.x, rect.bottom);

	int ratio = CGraph::m_nRatio;
	ratio /= (ratio / 100) + 1;

	CString str;
	PointF strPt;
	SolidBrush brush(Color(0,0,0));
	Gdiplus::Font F(_T("Arial"), ratio / 3, FontStyleRegular, UnitPixel);
	for (int i = pt.x % ratio; i < rect.right; i += ratio)
	{
		G.DrawLine(&pen, i, pt.y - 3, i, pt.y + 3);
		str.Format(_T("%.2lf"), (double)((i - pt.x) / ratio) / (CGraph::m_nRatio / 100 + 1));
		strPt.X = REAL(i), strPt.Y = REAL(pt.y);
		G.DrawString(str, str.GetLength(), &F, strPt, &brush);
	}
	for (int i = pt.y % ratio; i < rect.bottom; i += ratio)
	{
		G.DrawLine(&pen, pt.x - 3, i, pt.x + 3, i);
		str.Format(_T("%.2lf"), (double)-((i - pt.y) / ratio) / (CGraph::m_nRatio / 100 + 1));
		strPt.X = REAL(pt.x), strPt.Y = REAL(i);
		G.DrawString(str, str.GetLength(), &F, strPt, &brush);
	}
}

