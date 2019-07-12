#include "stdafx.h"
#include "Graph.h"

int CGraph::m_nRatio = 30;
int CGraph::m_nDx = 0;
int CGraph::m_nDy = 0;

CGraph::CGraph() : m_nThick(1), m_Color(0,0,0)
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

int CGraph::f(int x)
{
	int degree = m_Coeff.size() - 1; // 최고차수 = 항 갯수 - 1
	double result = 0.0;
	for (auto i : m_Coeff)
		result += i * pow(double(x) / m_nRatio, degree--);
	return int(round(result * m_nRatio));
}

