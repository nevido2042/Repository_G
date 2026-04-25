#pragma once
#include "afxdialogex.h"


// CDlgAddAdr 대화 상자

class CDlgAddAdr : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAddAdr)

public:
	CDlgAddAdr(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgAddAdr();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = ID_Add_Adr };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CString m_strPhone;
};
