#pragma once
#include <cmath>

class CPixelPainter
{
public:
	static void DrawHollowCircle(CDC* pDC, CPoint center, double radius, COLORREF color);
	static void DrawFilledCircle(CDC* pDC, CPoint center, int size, COLORREF color);
};
