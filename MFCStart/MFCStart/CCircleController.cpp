#include "pch.h"
#include "CCircleController.h"
#include "MFCStartDlg.h"
#include "Resource.h"
#include <thread>
#include <random>
#include <chrono>

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

void CCircleController::OnRandomMove()
{
	if (!m_model.IsReadyForCircle())
	{
		CString strMsg;
		strMsg.LoadString(IDS_ERR_NEED_3_POINTS);
		::AfxMessageBox(strMsg);
		return;
	}

	// 스레드에 전달할 포인터 (수명 주의: 다이얼로그 종료 시 스레드 제어 로직 필요할 수 있음)
	CCircleModel* pModel = &m_model;
	CMFCStartDlg* pView = &m_view;

	std::thread worker([pModel, pView]() {
		CRect rect;
		pView->GetClientRect(&rect);

		std::random_device rd;
		std::mt19937 gen(rd());
		
		int radius = pModel->m_nPointRadius;
		int minX = radius;
		int maxX = max(radius, rect.Width() - radius);
		int minY = radius;
		int maxY = max(radius, rect.Height() - radius);

		std::uniform_int_distribution<> disX(minX, maxX);
		std::uniform_int_distribution<> disY(minY, maxY);

		for (int i = 0; i < 10; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				pModel->MovePoint(j, CPoint(disX(gen), disY(gen)));
			}

			// 메인 UI 스레드에 화면 갱신 요청
			pView->PostMessage(WM_USER_REFRESH_UI);
			
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}
	});

	worker.detach(); // 독립 실행
}
