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
	afx_msg void CreateFunc();
	afx_msg void Delete();
	afx_msg void SaveFunction();
	afx_msg void OpenFunction();
	afx_msg void ToggleRuller();
	afx_msg void ToggleNumber();
	afx_msg void Minimize();

	afx_msg void OnLButtonDown(UINT nFlag, CPoint& pt);
	afx_msg void OnZoom(short zDelta);
	afx_msg void OnScreenMove(int dx, int dy);
	afx_msg void OnDraw(Graphics &G, CRect& rect);

private:
	CRect m_Rect;
	list<Selectee> m_Selee;
	list<CGraph*> m_Funs;
	CString GetPath(BOOL bIsOpen) const;

	bool m_bNumber;
	bool m_bRuller;

	void DrawCoordinate(Graphics&, CRect&) const;
	void DrawSelected(Graphics&, CRect&) const;
};

