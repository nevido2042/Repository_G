// CDlgAddAdr.cpp: 구현 파일
//

#include "pch.h"
#include "AdrBook.h"
#include "afxdialogex.h"
#include "CDlgAddAdr.h"


// CDlgAddAdr 대화 상자

IMPLEMENT_DYNAMIC(CDlgAddAdr, CDialogEx)

CDlgAddAdr::CDlgAddAdr(CWnd* pParent /*=nullptr*/)
	: CDialogEx(ID_Add_Adr, pParent)
	, m_strName(_T(""))
	, m_strPhone(_T(""))
{

}

CDlgAddAdr::~CDlgAddAdr()
{
}

void CDlgAddAdr::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Text(pDX, IDC_PHONE, m_strPhone);
}


BEGIN_MESSAGE_MAP(CDlgAddAdr, CDialogEx)
END_MESSAGE_MAP()


// CDlgAddAdr 메시지 처리기
