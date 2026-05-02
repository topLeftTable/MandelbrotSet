#include "ComplexPlane.h"
#include <cmath>
#include <complex>
#include <cstdint>
#include <thread>

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

void ComplexPlane::renderThread(int yFloor, int yCeil)
{
	for (int i = yFloor; i < yCeil; i++)
	{
		for (int j = 0; j < m_pixel_size.x; j++)
		{
			m_vArray[j + i * m_pixel_size.x].position = {static_cast<float>(j),
														 static_cast<float>(i)};
			const int iterations = countIterations(mapPixelToCoords({j, i}));
			uint8_t r = 0, g = 0, b = 0;
			iterationsToRGB(iterations, r, g, b);
			m_vArray[j + i * m_pixel_size.x].color = {r, g, b};
		}
	}
}

void ComplexPlane::updateRender()
{
	if (m_state == CALCULATING)
	{
		int numOfThreads = thread::hardware_concurrency() - 1;
		int chunkSize = m_pixel_size.y / numOfThreads;
		vector<thread> threads;
		for (int i = 0; i < numOfThreads; i++)
		{
			int currFloor = i * chunkSize;
			int currCeil =
				(i == numOfThreads - 1) ? m_pixel_size.y : (i + 1) * chunkSize;
			threads.push_back(
				thread(&ComplexPlane::renderThread, this, currFloor, currCeil));
		}
		for (thread &t : threads)
		{
			t.join();
		}
		m_state = DISPLAYING;
	}
}

int ComplexPlane::countIterations(Vector2f coord)
{
	complex<double> c(coord.x, coord.y);
	complex<double> z = c;
	int i = 0;
	while (abs(z) < 2.0 && i < MAX_ITER)
	{
		z = z * z + c;
		i++;
	}
	return i;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b)
{
	double t = mapRange(count, 0, MAX_ITER, 0, (numbers::pi / 2));
	r = sin(t) * 255;
	g = sin(2 * t) * 255;
	b = pow(cos(t), 3.00) * 255;
}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	Vector2f temp;
	temp.x =
		(static_cast<float>(m_plane_center.x - (m_plane_size.x / 2.00)) +
		 (static_cast<float>(mousePixel.x) / m_pixel_size.x) * m_plane_size.x);
	temp.y =
		(static_cast<float>(m_plane_center.y - (m_plane_size.y / 2.00)) +
		 (static_cast<float>(mousePixel.y) / m_pixel_size.y) * m_plane_size.y);
	return temp;
}

double ComplexPlane::mapRange(double n, double fromLow, double fromHigh,
							  double toLow, double toHigh)
{
	return ((n - fromLow) / (fromHigh - fromLow)) * (toHigh - toLow) + toLow;
}