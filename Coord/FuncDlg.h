#pragma once
#include <vector>
#include "Fract.h"

using namespace std;

// CFuncDlg 대화 상자
class CGraph;

class CFuncDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFuncDlg)

public:
	CFuncDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFuncDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	using Terms = vector<CFract>;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	DECLARE_MESSAGE_MAP()
private:
	CStatic m_ctrlText;
	Color m_Color;
	Terms m_Coeff;
	
	int m_nRadio;
	int m_nThick;
	void OnRadioClick(UINT value);

public:
	CGraph* GetNewFunc();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBnClickedColor();
	afx_msg void OnEnChangeEdit2();
};
