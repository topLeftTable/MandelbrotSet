//
// Created by logandev on 5/1/26.
//

#include "ComplexPlane.h"

#include "SFML/Graphics/RenderTarget.hpp"

#include <sstream>

using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{

	Vector2i pixelSize = {pixelWidth, pixelHeight};
	m_pixel_size = pixelSize;

	m_aspectRatio = (pixelHeight * 1.0) / (pixelWidth * 1.0);

	m_plane_center = {0, 0};

	m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};

	m_zoomCount = 0;

	m_state = State::CALCULATING;

	//FIXME
	//VertexArray = Points(pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{

}

void ComplexPlane::zoomOut()
{

}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = State::CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);;
}

void ComplexPlane::loadText(Text &text)
{
	ostringstream textStream;
	textStream<<"Mandelbrot Set"<<endl;
	textStream<<"Center: ("<<m_plane_center.x<<','<<m_plane_center.y<<')'<<endl;
	textStream<<"Cursor: ("<<m_mouseLocation.x<<','<<m_mouseLocation.y<<')'<<endl;
	textStream<<"Left-click to Zoom in"<<endl;
	textStream<<"Right-click to Zoom out"<<endl;

	text.setString(textStream.str());
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