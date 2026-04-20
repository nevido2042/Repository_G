#include "pch.h"
#include "CCircleModel.h"
#include <cmath>

CCircleModel::CCircleModel()
	: m_nPointRadius(5)
	, m_nThickness(1)
	, m_nDraggedIndex(-1)
{
}

CCircleModel::~CCircleModel()
{
}

void CCircleModel::AddPoint(CPoint pt)
{
	if (m_vPoints.size() < 3)
	{
		m_vPoints.push_back(pt);
	}
}

void CCircleModel::MovePoint(int index, CPoint pt)
{
	if (index >= 0 && index < static_cast<int>(m_vPoints.size()))
	{
		m_vPoints[index] = pt;
	}
}

void CCircleModel::Reset()
{
	m_vPoints.clear();
	m_nDraggedIndex = -1;
}

int CCircleModel::HitTest(CPoint pt)
{
	for (int i = 0; i < static_cast<int>(m_vPoints.size()); i++)
	{
		int dx = m_vPoints[i].x - pt.x;
		int dy = m_vPoints[i].y - pt.y;
		if (sqrt((double)dx * dx + (double)dy * dy) <= m_nPointRadius + 2)
		{
			return i;
		}
	}
	return -1;
}

bool CCircleModel::IsReadyForCircle() const
{
	return m_vPoints.size() == 3;
}