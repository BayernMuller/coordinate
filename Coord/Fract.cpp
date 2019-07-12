#include "stdafx.h"
#include "Fract.h"


CFract::~CFract()
{
}

CFract CFract::operator+(CFract & t)
{
	if (m_nMom != t.m_nMom)
		Reduce(t);
	CFract result(m_nSon + t.m_nSon, m_nMom);
	result.Reduction();
	return result;
}

CFract CFract::operator-(CFract & t)
{
	if (m_nMom != t.m_nMom)
		Reduce(t);
	CFract result(m_nSon - t.m_nSon, m_nMom);
	result.Reduction();
	return result;
}

CFract CFract::operator*(CFract & t)
{
	CFract result(m_nSon * t.m_nSon, m_nMom * t.m_nMom);
	result.Reduction();
	return result;
}

CFract CFract::operator/(CFract & t)
{
	CFract result(m_nSon * t.m_nMom, m_nMom * t.m_nSon);
	result.Reduction();
	return result;
}

CFract CFract::operator=(CFract & t)
{
	m_nMom = t.m_nMom;
	m_nSon = t.m_nSon;
	return *this;
}

CFract::operator double()
{
	return (double)m_nSon / m_nMom;
}

int CFract::Gcd(int a, int b)
{
	if (!b)
		return a;
	return Gcd(b, a % b);
}

int CFract::Lcm(int a, int b)
{
	return (a * b) / Gcd(a, b);
}

void CFract::Reduction()
{
	int gcd = Gcd(m_nSon, m_nMom);
	m_nSon /= gcd;
	m_nMom /= gcd;
}

void CFract::Reduce(CFract & t)
{
	int delta = Lcm(t.m_nMom, m_nMom) / m_nMom;
	m_nMom *= delta;
	m_nSon *= delta;
	delta *= t.m_nMom * m_nMom;
	t.m_nMom *= delta;
	t.m_nSon *= delta;
}
