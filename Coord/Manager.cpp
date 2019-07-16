#include "stdafx.h"
#include "Manager.h"
#include "Linear.h"
#include "Rational.h"
#include "Circle.h"
#include "FuncDlg.h"


CManager::CManager() : m_bNumber(true), m_bRuller(true)
{
	
}

CManager::~CManager()
{
	for (auto i : m_Funs)
		delete i;
}

void CManager::OnDraw(Graphics &G, CRect & rect)
{
	G.SetSmoothingMode(SmoothingModeAntiAlias);
	DrawCoordinate(G, rect);
	for (auto i : m_Funs)
		i->Draw(G, rect);
	DrawSelected(G, rect);
	m_Rect = rect;
}

void CManager::OnLButtonDown(UINT nFlag, CPoint& pt)
{
	for (auto i = m_Funs.begin(); i != m_Funs.end(); i++)
		if ((*i)->IsSelected(pt, m_Rect.CenterPoint()))
		{
			if (nFlag != MK_CONTROL)
				m_Selee.clear();
			for (auto itr : m_Selee)
				if (itr == i)
					return;
			m_Selee.push_back(i);
			return;
		}
	m_Selee.clear();
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

CString CManager::GetPath(BOOL bIsOpen) const
{
	CString str(_T("Function Information (*.fun)|*.fun|"));
	CFileDialog dlg(bIsOpen, _T("fun"), _T("*.fun"), OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, str, NULL);
	if (dlg.DoModal() == IDOK)
		return dlg.GetPathName();
	return _T("");
}

void CManager::DrawCoordinate(Graphics & G, CRect & rect) const
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
	Gdiplus::Font F(_T("Arial"), (REAL)ratio / 3, FontStyleRegular, UnitPixel);
	for (int i = pt.x % ratio; i < rect.right; i += ratio)
	{
		if (m_bRuller)
			G.DrawLine(&pen, i, pt.y - 3, i, pt.y + 3);
		if (m_bNumber)
		{
			str.Format(_T("%.2lf"), (double)((i - pt.x) / ratio) / (CGraph::m_nRatio / 100 + 1));
			strPt.X = REAL(i), strPt.Y = REAL(pt.y);
			G.DrawString(str, str.GetLength(), &F, strPt, &brush);
		}
	}
	for (int i = pt.y % ratio; i < rect.bottom; i += ratio)
	{
		if (m_bRuller)
			G.DrawLine(&pen, pt.x - 3, i, pt.x + 3, i);
		if (m_bNumber)
		{
			str.Format(_T("%.2lf"), (double)-((i - pt.y) / ratio) / (CGraph::m_nRatio / 100 + 1));
			strPt.X = REAL(pt.x), strPt.Y = REAL(i);
			G.DrawString(str, str.GetLength(), &F, strPt, &brush);
		}
	}
}

void CManager::DrawSelected(Graphics & G, CRect & rect) const
{
	int cnt = 0;
	Gdiplus::Font F(_T("Arial"), 20, Gdiplus::FontStyleBold, Gdiplus::UnitPixel);
	for (const auto i : m_Selee)
	{
		auto str = (*i)->GetString();
		SolidBrush B(Color((*i)->GetColor()));
		G.DrawString(str, str.GetLength(), &F, PointF(100.0, 100.0 + 20 * cnt++), &B);
	}
}

void CManager::CreateFunc()
{
	CFuncDlg dlg;
	vector<CFract> v;
	if (dlg.DoModal() == IDOK)
		m_Funs.push_back(dlg.GetNewFunc());
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

void CManager::SaveFunction() 
{
	CString path = GetPath(FALSE);
	if (path.IsEmpty())
		return;
	CFile file;
	file.Open(path, CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	ar << m_Funs.size();
	for (const auto i : m_Funs)
		i->Selialize(ar);
	ar.Close();
	file.Close();
}

void CManager::OpenFunction() 
{
	CString path = GetPath(TRUE);
	if (path.IsEmpty())
		return;
	int kind;
	size_t size;
	CFile file;
	file.Open(path, CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	ar >> size;
	for (size_t i = 0; i < size; i++)
	{
		CGraph *newfun = nullptr;
		ar >> kind;
		switch (kind)
		{
		case CGraph::line:
			newfun = new CLinear;
			break;
		case CGraph::curve:
			newfun = new CCurve;
			break;
		case CGraph::rational:
			newfun = new CRational;
			break;
		case CGraph::circle:
			newfun = new CCircle;
			break;
		}
		newfun->Selialize(ar);
		m_Funs.push_back(newfun);
	}
	ar.Close();
	file.Close();
}

void CManager::ToggleRuller()
{
	m_bRuller = !m_bRuller;
}

void CManager::ToggleNumber()
{
	m_bNumber = !m_bNumber;
}


void CManager::Minimize()
{
	CGraph::m_nDx = CGraph::m_nDy = 0;
	CGraph::m_nRatio = 30;
}
