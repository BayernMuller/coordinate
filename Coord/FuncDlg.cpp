// FuncDlg.cpp: 구현 파일
//

#include "stdafx.h"
#include "Coord.h"
#include "FuncDlg.h"
#include "afxdialogex.h"
#include "Linear.h"
#include "Rational.h"
#include "Circle.h"

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
	if (m_nRadio == value - IDC_RADIO1)
	UpdateData(TRUE);
	LPCWSTR str[] =
	{
		L"x에 대해 내림차순으로 정리한 식의 계수들을 차례대로 입력",
		L"k / (x - p) + q 에서 k, p, q 순으로 입력",
		L"a(x - b)^2 + c(y - d)^2 = r^2 에서 a b c d r 순으로 입력"
	};
	m_ctrlText.SetWindowText(str[value - IDC_RADIO1]);
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
	CString str, frac[2];
	int idx = 0;
	GetDlgItem(IDC_EDIT1)->GetWindowText(str);
	if (str[str.GetLength() - 1] != L' ')
		str.AppendChar(L' ');
	for (int i = 0; i < str.GetLength(); i++)
	{
		if (iswdigit(str[i]) || str[i] == L'-')
		{
			frac[idx].AppendChar(str[i]);
		}
		else if (str[i] == L'/')
		{
			++idx %= 2;
		}
		else if (str[i] == L' ')
		{
			if (idx) m_Coeff.push_back(CFract(_wtoi(frac[0]), _wtoi(frac[1])));
			else m_Coeff.push_back(CFract(_wtoi(frac[0])));
			idx = 0, frac[0] = frac[1] = L"";
		}
		else
		{
			AfxMessageBox(_T("잘못된 입력입니다."));
			return;
		}
	}
	GetDlgItem(IDC_EDIT2)->GetWindowText(str);
	m_nThick = _wtoi(str);
	CDialogEx::OnOK();
}


void CFuncDlg::OnBnClickedColor()
{
	CColorDialog dlg;
	dlg.DoModal();
	m_Color.SetFromCOLORREF(dlg.GetColor());
}


void CFuncDlg::OnEnChangeEdit2()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
