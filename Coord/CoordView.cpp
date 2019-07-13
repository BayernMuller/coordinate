
// CoordView.cpp: CCoordView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "Coord.h"
#endif

#include "CoordDoc.h"
#include "CoordView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoordView

IMPLEMENT_DYNCREATE(CCoordView, CView)

BEGIN_MESSAGE_MAP(CCoordView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_COMMAND_RANGE(ID_MENU_CREATE, ID_MENU_NUMBER, &CCoordView::OnFunctionMenu)
END_MESSAGE_MAP()

// CCoordView 생성/소멸

CCoordView::CCoordView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	srand((unsigned int)time(NULL));
}

CCoordView::~CCoordView()
{
}

BOOL CCoordView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.
	cs.style &= ~WS_BORDER;
	return CView::PreCreateWindow(cs);
}

// CCoordView 그리기

void CCoordView::OnDraw(CDC* pDC)
{
	CCoordDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	CRect rect;
	GetClientRect(&rect);
	Rect rclClient(rect.left, rect.top, rect.Width(), rect.Height());

	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	CBitmap memBmp;
	memBmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	CBitmap *pOldBitmap = MemDC.SelectObject(&memBmp);
	Graphics mem(MemDC.m_hDC);
	mem.SetSmoothingMode(SmoothingModeAntiAlias);
	mem.FillRectangle(&SolidBrush(Color(255,255,255)), rclClient);

	m_Manager.Draw(mem, rect);

	pDC->BitBlt(0, 0, rect.right, rect.bottom, &MemDC, 0, 0, SRCCOPY);
	MemDC.SelectObject(pOldBitmap);
}

BOOL CCoordView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CCoordView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CCoordView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CCoordView 진단

#ifdef _DEBUG
void CCoordView::AssertValid() const
{
	CView::AssertValid();
}

void CCoordView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCoordDoc* CCoordView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCoordDoc)));
	return (CCoordDoc*)m_pDocument;
}
#endif //_DEBUG


// CCoordView 메시지 처리기


void CCoordView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	m_Manager.Select(nFlags, point);
	m_StartPt = point;
	CView::OnLButtonDown(nFlags, point);
}


void CCoordView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nChar == VK_DELETE)
	{
		m_Manager.Delete();
		Invalidate(TRUE);
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CCoordView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags == MK_CONTROL)
	{
		m_Manager.OnZoom(zDelta);
		Invalidate(TRUE);
	}
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

BOOL CCoordView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE;
}

void CCoordView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nFlags & MK_LBUTTON)
	{
		CPoint delta = m_StartPt - point;
		m_Manager.OnScreenMove(delta.x, delta.y);
		m_StartPt = point;
		Invalidate(TRUE);
	}
	CView::OnMouseMove(nFlags, point);
}

void CCoordView::OnFunctionMenu(UINT nID)
{
	void(CManager::*fp[])() =
	{
		&CManager::CreateFunc,
		&CManager::Delete,
		&CManager::Minimize,
		&CManager::MoveFunc,
		&CManager::ToggleRuller,
		&CManager::SelectedFunc,
		&CManager::ToggleNumber
	};
	(m_Manager.*fp[nID - ID_MENU_CREATE])();
	Invalidate(TRUE);	
}

