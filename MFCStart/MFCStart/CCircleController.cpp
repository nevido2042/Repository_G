#include "pch.h"
#include "CCircleController.h"
#include "MFCStartDlg.h"

CCircleController::CCircleController(CCircleModel& model, CMFCStartDlg& view)
	: m_model(model), m_view(view)
{
}

CCircleController::~CCircleController()
{
}

void CCircleController::OnLButtonDown(UINT nFlags, CPoint point)
{
	// UI -> Model 데이터 동기화
	m_view.SyncData(TRUE);

	// 모델에게 클릭 판정 요청
	m_model.m_nDraggedIndex = m_model.HitTest(point);

	if (m_model.m_nDraggedIndex != -1)
	{
		m_view.SetCapture();
	}
	else if (m_model.m_vPoints.size() < 3)
	{
		m_model.AddPoint(point);
		m_view.UpdateCoordinateDisplay();
		m_view.Invalidate();
	}
}

void CCircleController::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_model.m_nDraggedIndex != -1 && (nFlags & MK_LBUTTON))
	{
		m_model.MovePoint(m_model.m_nDraggedIndex, point);
		m_view.UpdateCoordinateDisplay();
		m_view.Invalidate();
	}
}

void CCircleController::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (m_model.m_nDraggedIndex != -1)
	{
		m_model.m_nDraggedIndex = -1;
		::ReleaseCapture();
	}
}

void CCircleController::OnReset()
{
	m_model.Reset();
	m_view.UpdateCoordinateDisplay();
	m_view.Invalidate();
}
