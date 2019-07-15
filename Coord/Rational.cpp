#include "stdafx.h"
#include "Rational.h"


CRational::CRational()
{
}


CRational::~CRational()
{
}


int CRational::f(int x)
{
	return (int)round((m_Coeff[0] / (double(x) / m_nRatio - m_Coeff[1]) + m_Coeff[2]) * m_nRatio);
}
