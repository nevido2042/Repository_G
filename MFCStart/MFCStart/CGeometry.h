#pragma once
#include <vector>
#include <cmath>

class CGeometry
{
public:
	static bool CalculateCircumcircle(const std::vector<CPoint>& points, CPoint& center, double& radius);
};
