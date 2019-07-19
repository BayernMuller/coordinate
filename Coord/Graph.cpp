#include "stdafx.h"
#include "Graph.h"

int CGraph::m_nRatio = 30;
int CGraph::m_nDx = 0;
int CGraph::m_nDy = 0;

CGraph::CGraph() : m_nThick(1), m_Color(0, 0, 0)
{

}

CGraph::~CGraph()
{
}

void CGraph::SetFunction(Terms args)
{
	m_Coeff.assign(args.begin(), args.end());
}

void CGraph::Initialize(Color color, int thick)
{
	m_Color = color;
	m_nThick = thick;
}

bool CGraph::IsSelected(CPoint& pt, CPoint& center)
{
	center.Offset(m_nDx, m_nDy);
	return abs((center.y - f(pt.x - center.x)) - pt.y) < 40;
}

CString CGraph::GetString()
{
	CString str = _T("y = ");
	for (int i = 0, deg = m_Coeff.size() - 1; i < (int)m_Coeff.size(); i++, deg--)
	{
		CString format, temp;
		if (m_Coeff[i].GetSon())
		{
			format = _T("%d");
			if (i)
				format.Insert(1, _T('+'));
			if (m_Coeff[i].GetMom() != 1)
			{
				format.Append(_T("/%d"));
				temp.Format(format, m_Coeff[i].GetSon(), m_Coeff[i].GetMom());
			}
			else
				temp.Format(format, m_Coeff[i].GetSon());
			if (deg)
			{
				temp += _T("x");
				if (deg > 1)
					temp.Format(_T("%s^%d"), temp, deg);
			}
		}
		str += temp;
	}
	return str;
}

void CGraph::Selialize(CArchive & ar, Child kind)
{
	if (kind == null)
		return;
	if (ar.IsStoring())
	{
		ar << kind;
		ar << m_Coeff.size();
		for (const auto i : m_Coeff)
		{
			ar << i.GetSon();
			ar << i.GetMom();
		}
		ar << m_Color.GetValue();
		ar << m_nThick;
	}
	else
	{
		ARGB color;
		int size, s, m, thick;
		ar >> size;
		for (int i = 0; i < size; i++)
		{
			ar >> s >> m;
			m_Coeff.push_back(CFract(s, m));
		}
		ar >> color;
		ar >> thick;
		m_Color.SetValue(color);
		m_nThick = thick;
	}
}


int CGraph::f(int x)
{
	int degree = m_Coeff.size() - 1; // 최고차수 = 항 갯수 - 1
	double result = 0.0;
	for (auto i : m_Coeff)
		result += i * pow(double(x) / m_nRatio, degree--);
	return int(round(result * m_nRatio));
}

