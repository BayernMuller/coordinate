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

	afx_msg void CreateFunc();
	afx_msg void Delete();
	afx_msg void MoveFunc();
	afx_msg void ToggleRuller();
	afx_msg void ToggleNumber();
	afx_msg void SelectedFunc();
	afx_msg void Minimize();
private:
	CRect m_Rect;
	list<CGraph*> m_Funs;
	list<Selectee> m_Selee;
	bool m_bNumber;
	bool m_bRuller;

	void DrawCoordinate(Graphics&, CRect&);	
};

