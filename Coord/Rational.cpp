#include "stdafx.h"
#include "Rational.h"


CRational::CRational()
{
}


CRational::~CRational()
{
}

void CRational::Selialize(CArchive & ar, Child kind)
{
	CGraph::Selialize(ar, rational);
}

CString CRational::GetString()
{
	int s, m;
	CString str, temp[3];
	for (int i = 0; i < 3; i++)
	{
		CString format = _T("%d");
		m = m_Coeff[i].GetMom(), s = m_Coeff[i].GetSon();
		if (i)
			format.Insert(1, _T('+'));
		if (m_Coeff[i].GetMom() != 1)
			format.Append(_T("/%d"));
		temp[i].Format(format, s * ((i == 1) ? -1 : 1), m);
	}
	str.Format(_T("y = (%s) / (x%s) %s"), temp[0], temp[1], temp[2]);
	return str;
}


int CRational::f(int x)
{
	return (int)round((m_Coeff[0] / (double(x) / m_nRatio - m_Coeff[1]) + m_Coeff[2]) * m_nRatio);
}
