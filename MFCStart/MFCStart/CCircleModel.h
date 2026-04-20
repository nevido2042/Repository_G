#pragma once
#include <vector>
#include <atltypes.h>

class CCircleModel
{
public:
	CCircleModel();
	virtual ~CCircleModel();

	// Data
	std::vector<CPoint> m_vPoints;
	int m_nPointRadius;
	int m_nThickness;
	int m_nDraggedIndex;

	// Logic
	void AddPoint(CPoint pt);
	void MovePoint(int index, CPoint pt);
	void Reset();
	int HitTest(CPoint pt);
	bool IsReadyForCircle() const;
};