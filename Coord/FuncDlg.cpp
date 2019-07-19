// FuncDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Coord.h"
#include "FuncDlg.h"
#include "afxdialogex.h"
#include "Linear.h"
#include "Rational.h"
#include "Circle.h"

#pragma warning(disable:4996)
// CFuncDlg 대화 상자

IMPLEMENT_DYNAMIC(CFuncDlg, CDialogEx)

CFuncDlg::CFuncDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, m_nRadio(0)
	, m_Color(0, 0, 0)
	, m_nThick(1)
{

}

CFuncDlg::~CFuncDlg()
{

}

void CFuncDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_nRadio);
	DDX_Control(pDX, IDC_SUCCEED, m_ctrlText);
}


BEGIN_MESSAGE_MAP(CFuncDlg, CDialogEx)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_RADIO1, IDC_RADIO3, &CFuncDlg::OnRadioClick)
	ON_BN_CLICKED(IDC_BUTTON1, &CFuncDlg::OnBnClickedColor)
	ON_EN_CHANGE(IDC_EDIT2, &CFuncDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CFuncDlg 메시지 처리기

void CFuncDlg::OnRadioClick(UINT value)
{
	const static LPCWSTR str[] =
	{
		L"x에 대해 내림차순으로 정리한 식의 계수들을 차례대로 입력",
		L"k / (x - p) + q 에서 k, p, q 순으로 입력",
		L"(x - a)^2 + (y - b)^2 = r^2 에서 a, b, r 순으로 입력"
	};
	if (m_nRadio == value - IDC_RADIO1)
	UpdateData(TRUE);
	m_ctrlText.SetWindowText(str[value - IDC_RADIO1]);
}

CFract CFuncDlg::ToFract(const CString & str)
{
	wchar_t* psz = const_cast<wchar_t*>(str.operator const wchar_t*());
	int idx = str.Find(L'/'), s = 1, m = 1;
	if (idx != EOF)
	{
		psz[idx] = L'\0';
		
		s = _wtoi(psz);
		psz += idx + 1;
		m = _wtoi(psz);
	}
	else
		s = _wtoi(str);
	return CFract(s, m);
}

CGraph * CFuncDlg::GetNewFunc()
{
	CGraph* newFunc = nullptr;
	switch (m_nRadio)
	{
	case 0:
		if (m_Coeff.size() == 2)
			newFunc = new CLinear;
		else
			newFunc = new CCurve;
		break;
	case 1:
		newFunc = new CRational;
		break;
	case 2:
		newFunc = new CCircle;
		break;
	}
	newFunc->Initialize(m_Color, m_nThick);
	newFunc->SetFunction(m_Coeff);
	return newFunc;
}

BOOL CFuncDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	OnRadioClick(IDC_RADIO1);
	return TRUE; 
}


void CFuncDlg::OnOK()
{
	UpdateData(TRUE);
	m_Coeff.clear();
	CString str;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	for (int i = 0; i < str.GetLength(); i++)
		if (!(iswdigit(str[i]) || str[i] == L'-' || str[i] == L'/' || str[i] == L' '))
		{
			AfxMessageBox(_T("잘못된 입력입니다."));
			return;
		}
	wchar_t* psz = wcstok(const_cast<wchar_t*>(str.operator const wchar_t*()), L" ");;
	while (psz)
	{
		if (!StrCmpW(psz, L"-"))
		{
			AfxMessageBox(_T("잘못된 입력입니다."));
			return;
		}
		m_Coeff.push_back(ToFract(psz));
		psz = wcstok(nullptr, L" ");
	}
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	m_nThick = _wtoi(str);
	if (m_nRadio)
		if (m_Coeff.size() != 3 || (m_nRadio == 2 && m_Coeff[2] < 0))
		{
			AfxMessageBox(_T("잘못된 입력입니다."));
			return;
		}
	CDialogEx::OnOK();
}


void CFuncDlg::OnBnClickedColor()
{
	CColorDialog dlg;
	dlg.DoModal();
	m_Color.SetFromCOLORREF(dlg.GetColor());
}


void CFuncDlg::OnEnChangeEdit2()
{}
