#pragma once
#include <list>
using namespace std;
class CGraph;

class CManager
{
	using Selectee = list<CGraph*>::iterator;
public:
	CManager();
	~CManager();
	void Draw(Graphics &G, CRect& rect);
	void Select(UINT nFlag, CPoint& pt);
	void OnZoom(short zDelta);
	void OnScreenMove(int dx, int dy);
	void Init();
	void Delete();

private:
	CRect m_Rect;
	list<CGraph*> m_Funs;
	list<Selectee> m_Selee;
	
	void DrawCoordinate(Graphics &G, CRect& rect);
};

