#include "ComplexPlane.h"
#include <cmath>
#include <cstdint>
#include <complex>

#include "SFML/Graphics/RenderTarget.hpp"

#include <sstream>

using namespace std;

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = {pixelWidth, pixelHeight};
	m_aspectRatio = (pixelHeight * 1.0) / (pixelWidth * 1.0);
	m_plane_center = {0, 0};
	m_plane_size = {BASE_WIDTH, BASE_HEIGHT * m_aspectRatio};
	m_zoomCount = 0;
	m_state = CALCULATING;
	m_vArray = VertexArray(Points, pixelWidth * pixelHeight);
}

void ComplexPlane::draw(RenderTarget &target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	float xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = {xSize, ySize};
	m_state = CALCULATING;
}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	float xSize = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	float ySize = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = {xSize, ySize};
	m_state = CALCULATING;
}

void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = CALCULATING;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel)
{
	m_mouseLocation = mapPixelToCoords(mousePixel);
}

void ComplexPlane::loadText(Text &text)
{
	ostringstream textStream;
	textStream << "Mandelbrot Set" << endl;
	textStream << "Center: (" << m_plane_center.x << ',' << m_plane_center.y
			   << ')' << endl;
	textStream << "Cursor: (" << m_mouseLocation.x << ',' << m_mouseLocation.y
			   << ')' << endl;
	textStream << "Left-click to Zoom in" << endl;
	textStream << "Right-click to Zoom out" << endl;

	text.setString(textStream.str());
}

void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		for (int i = 0; i < m_pixel_size.y; i++)
		{
			for (int j = 0; j < m_pixel_size.x; j++)
			{
				m_vArray[j + i * m_pixel_size.x].position = {
					static_cast<float>(j), static_cast<float>(i)};
				const int iterations =
					countIterations(mapPixelToCoords({j, i}));
				uint8_t r = 0, g = 0, b = 0;
				iterationsToRGB(iterations, r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = {r, g, b};
			}
		}
		m_state = DISPLAYING;
	}
}

int ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c (coord.x, coord.y);
	complex<double> z  = c;
	int i = 0;
	while(abs(z) < 2.0 && i < MAX_ITER)
	{
		z = z*z + c;
		i++;
	}
	return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
	if (count == MAX_ITER)
	{
		r = 0;
		g = 0;
		b = 0;
	}
	else if (count <= 51)
	{
		r = 240;
		g = 0;
		b = 255;
	}
	else if (count <= 102)
	{
		r = 0;
		g = 255;
		b = 160;
	}
	else if (count <= 153)
	{
		r = 30;
		b = 255;
		g = 0;
	}
	else if (count <= 204)
	{
		r = 255;
		g = 255;
		b = 0;
	}
	else
	{
		r = 255;
		g = 5;
		b = 0;
	}
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	Vector2f temp;
	temp.x = (static_cast<float>(m_plane_center.x - (m_plane_size.x / 2.00)) + (static_cast<float>(mousePixel.x) / m_pixel_size.x) * m_plane_size.x);
	temp.y = (static_cast<float>(m_plane_center.y - (m_plane_size.y / 2.00)) + (static_cast<float>(mousePixel.y) / m_pixel_size.y) * m_plane_size.y);
	return temp;
}
