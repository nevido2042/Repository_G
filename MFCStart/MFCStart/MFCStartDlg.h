
// MFCStartDlg.h: 헤더 파일
//

#pragma once


#include "CGeometry.h"
#include "CPixelPainter.h"

#include "CCircleModel.h"
#include "CCircleController.h"
#include <memory>

#define WM_USER_REFRESH_UI (WM_USER + 1)

// CMFCStartDlg 대화 상자
class CMFCStartDlg : public CDialogEx
{
// 생성입니다.
public:
	CMFCStartDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

	void UpdateCoordinateDisplay();
	BOOL SyncData(BOOL bSaveAndValidate = TRUE) { return UpdateData(bSaveAndValidate); }

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCSTART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.
	virtual BOOL PreTranslateMessage(MSG* pMsg) override; // 키 입력 가로채기


// 구현입니다.
protected:
	HICON m_hIcon;
	CCircleModel m_model; // 데이터 모델
	std::unique_ptr<CCircleController> m_controller;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnRandomMove();
	afx_msg LRESULT OnUserRefreshUI(WPARAM wParam, LPARAM lParam);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	DECLARE_MESSAGE_MAP()
};
