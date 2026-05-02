//
// Created by logandev on 5/1/26.
//

#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	Vector2i pixelSize = {pixelWidth, pixelHeight};
	m_pixel_size = pixelSize;
}
