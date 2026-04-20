#include "pch.h"
#include "CGeometry.h"

bool CGeometry::CalculateCircumcircle(const std::vector<CPoint>& points, CPoint& center, double& radius)
{
	if (points.size() < 3)
	{
		return false;
	}

	double x1 = static_cast<double>(points[0].x), y1 = static_cast<double>(points[0].y);
	double x2 = static_cast<double>(points[1].x), y2 = static_cast<double>(points[1].y);
	double x3 = static_cast<double>(points[2].x), y3 = static_cast<double>(points[2].y);

	double D = 2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2));
	
	if (std::abs(D) < 100.0)
	{
		return false; // 거의 일직선상에 있는 경우 제외
	}

	double cx = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) * (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / D;
	double cy = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) * (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / D;

	center.x = static_cast<long>(cx);
	center.y = static_cast<long>(cy);

	radius = std::sqrt(std::pow(cx - x1, 2) + std::pow(cy - y1, 2));

	if (radius > 5000.0)
	{
		return false;
	}

	return true;
}
