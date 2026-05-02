//
// Created by logandev on 5/1/26.
//

#ifndef MANDELBROTSET_COMPLEXPLANE_H
#define MANDELBROTSET_COMPLEXPLANE_H

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Text.hpp"

using namespace sf;

class ComplexPlane : Drawable
{
public:
	ComplexPlane(int pixelWidth, int pixelHeight);
	const void draw(RenderTarget &target, RenderStates states);
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

	VertexArray m_vArray;
	RenderStates m_state;
	Vector2f m_mouseLocation;
	Vector2i m_pixel_size;
	Vector2f m_plane_center;
	Vector2f m_plane_size;
	int m_zoomCount;
	float m_aspectRatio;
};

#endif // MANDELBROTSET_COMPLEXPLANE_H
