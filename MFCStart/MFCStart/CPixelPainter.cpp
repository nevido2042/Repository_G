#include "pch.h"
#include "CPixelPainter.h"

void CPixelPainter::DrawHollowCircle(CDC* pDC, CPoint center, double radius, int thickness, COLORREF color)
{
	int r = static_cast<int>(radius + (thickness / 2.0) + 0.5);
	for (int y = center.y - r - 1; y <= center.y + r + 1; y++)
	{
		for (int x = center.x - r - 1; x <= center.x + r + 1; x++)
		{
			double dist = std::sqrt(std::pow(x - center.x, 2) + std::pow(y - center.y, 2));
			// 두께(thickness)만큼 칠함
			if (std::abs(dist - radius) < (thickness / 2.0))
			{
				pDC->SetPixel(x, y, color);
			}
		}
	}
}

void CPixelPainter::DrawFilledCircle(CDC* pDC, CPoint center, int size, COLORREF color)
{
	for (int y = center.y - size; y <= center.y + size; y++)
	{
		for (int x = center.x - size; x <= center.x + size; x++)
		{
			double dist = std::sqrt(std::pow(x - center.x, 2) + std::pow(y - center.y, 2));
			if (dist <= size)
			{
				pDC->SetPixel(x, y, color);
			}
		}
	}
}
