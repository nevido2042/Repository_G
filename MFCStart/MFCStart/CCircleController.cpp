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
	m_bStopRequest = true; // 실행 중인 스레드가 있다면 중단 요청
	m_model.Reset();
	m_view.UpdateCoordinateDisplay();
	m_view.Invalidate();
}

void CCircleController::OnRandomMove()
{
	if (m_bIsRunning)
	{
		// 이미 실행 중이면 무시
		return;
	}

	if (!m_model.IsReadyForCircle())
	{
		CString strMsg;
		strMsg.LoadString(IDS_ERR_NEED_3_POINTS);
		::AfxMessageBox(strMsg);
		return;
	}

	m_bIsRunning = true;
	m_bStopRequest = false;

	CCircleModel* pModel = &m_model;
	CMFCStartDlg* pView = &m_view;
	
	// atomic 변수들에 접근하기 위해 this를 캡처하거나 별도 변수 사용
	// 안전을 위해 클래스 멤버에 대한 참조를 람다에 전달
	std::thread worker([this, pModel, pView]() {
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

		const int totalCount = 10;
		for (int i = 0; i < totalCount; ++i)
		{
			if (m_bStopRequest) break; // 중단 요청 확인

			for (int j = 0; j < 3; ++j)
			{
				pModel->MovePoint(j, CPoint(disX(gen), disY(gen)));
			}

			// 메인 UI 스레드에 화면 갱신 및 남은 횟수 전달
			// wParam에 남은 횟수(1~10)를 실어서 보냄
			pView->PostMessage(WM_USER_REFRESH_UI, (WPARAM)(totalCount - i), 0);
			
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
		}

		// 종료 시 카운트 0 전달 및 상태 해제
		pView->PostMessage(WM_USER_REFRESH_UI, 0, 0);
		m_bIsRunning = false;
	});

	worker.detach();
}
