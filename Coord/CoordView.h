
// CoordView.h: CCoordView 클래스의 인터페이스
//

#pragma once
#include "Manager.h"

class CCoordView : public CView
{
protected: // serialization에서만 만들어집니다.
	CCoordView() noexcept;
	DECLARE_DYNCREATE(CCoordView)

// 특성입니다.
public:
	CCoordDoc* GetDocument() const;

// 작업입니다.
private:
	CManager m_Manager;
	CPoint m_StartPt;

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CCoordView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
private:
	
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnFunctionMenu(UINT nID);
};

#ifndef _DEBUG  // CoordView.cpp의 디버그 버전
inline CCoordDoc* CCoordView::GetDocument() const
   { return reinterpret_cast<CCoordDoc*>(m_pDocument); }
#endif

