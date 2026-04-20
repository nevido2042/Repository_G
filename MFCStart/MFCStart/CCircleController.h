#pragma once

#include "CCircleModel.h"
#include <atomic>

// Forward declaration
class CMFCStartDlg;

class CCircleController
{
public:
	CCircleController(CCircleModel& model, CMFCStartDlg& view);
	~CCircleController();

	// Logic Handlers
	void OnLButtonDown(UINT nFlags, CPoint point);
	void OnMouseMove(UINT nFlags, CPoint point);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnReset();
	void OnRandomMove();

private:
	CCircleModel& m_model;
	CMFCStartDlg& m_view;

	std::atomic<bool> m_bIsRunning{ false };
	std::atomic<bool> m_bStopRequest{ false };
};
