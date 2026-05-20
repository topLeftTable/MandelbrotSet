/**
 * Copyright (C) 2022-2025 Ryan Hermle <rhermle>
 * Modified Works by LoganMD, WaitingKeptYouHuh, and deathsdebtor
 * Copyright (C) 2026 topLeftTable

MandlebrotSet is free software: you can redistribute it and/or modify
its terms under the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MandlebrotSet is distributed in the hope that it will be useful,
but WITHOUT WARRANTY. See <https://www.gnu.org/licenses/> for details.
**/

#ifndef MANDELBROTSET_COMPLEXPLANE_H
#define MANDELBROTSET_COMPLEXPLANE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Text.hpp"
#include <chrono>

using namespace std;
using namespace sf;

const unsigned int MAX_ITER = 128;
const float BASE_WIDTH = 4.0;
const float BASE_HEIGHT = 4.0;
const float BASE_ZOOM = 0.5;

enum State
{
	CALCULATING,
	DISPLAYING
};

class ComplexPlane : public Drawable
{
  public:
	ComplexPlane(int pixelWidth, int pixelHeight);
	void draw(RenderTarget &target, RenderStates states) const override;
	void zoomIn();
	void zoomOut();
	void setCenter(Vector2i mousePixel);
	void setMouseLocation(Vector2i mousePixel);
	void loadText(Text &text);
	void updateRender();

  private:
	int countIterations(Vector2f coord);
	void iterationsToRGB(size_t count, Uint8 &r, Uint8 &g, Uint8 &b);
	Vector2f mapPixelToCoords(Vector2i mousePixel);
	double mapRange(double n, double fromLow, double fromHigh, double toLow,
					double toHigh);
	void renderThread(int yFloor, int yCeil);

	VertexArray m_vArray;
	State m_state;
	Vector2f m_mouseLocation;
	Vector2i m_pixel_size;
	Vector2f m_plane_center;
	Vector2f m_plane_size;
	int m_zoomCount;
	float m_aspectRatio;
	chrono::steady_clock::time_point m_render_start;
	chrono::steady_clock::time_point m_render_end;
};

#endif // MANDELBROTSET_COMPLEXPLANE_H
