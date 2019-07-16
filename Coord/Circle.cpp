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

}

void CCircle::Selialize(CArchive & ar, Child kind)
{
	CGraph::Selialize(ar, circle);
}
