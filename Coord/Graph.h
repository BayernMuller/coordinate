#pragma once
#include <vector>
#include "Fract.h"
using namespace std;
class CGraph
{
protected:
	using Terms = vector<CFract>;
	
public:
	CGraph();
	~CGraph();
	Color GetColor() { return m_Color; }
	enum Child { null = -1, line, curve, rational, circle };
	virtual void Draw(Graphics& G, CRect& rect) = 0;
	virtual void SetFunction(Terms args);
	virtual bool IsSelected(CPoint& pt, CPoint& center);
	virtual CString GetString();
	virtual void Selialize(CArchive& ar, Child kind = null);

	void Initialize(Color color, int thick);
	static int m_nRatio;
	static int m_nDx, m_nDy;
	
protected:
	virtual int f(int x);
	int m_nThick;
	Color m_Color;
	Terms m_Coeff;

};

