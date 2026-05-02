//
// Created by logandev on 5/1/26.
//

#include "ComplexPlane.h"


ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{

	Vector2i pixelSize = {pixelWidth, pixelHeight};
	m_pixel_size = pixelSize;

	m_aspectRatio = (pixelHeight * 1.0) / (pixelWidth * 1.0);

	m_plane_center = {0, 0};

	m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};

	m_zoomCount = 0;


}

void ComplexPlane::draw(RenderTarget &target, RenderStates states) const
{

}

void ComplexPlane::zoomIn()
{

}

void ComplexPlane::zoomOut()
{

}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{

}

void ComplexPlane::loadText(Text &text)
{

}

void ComplexPlane::updateRender()
{

}


int ComplexPlane::countIterations(Vector2f coord)
{

}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}