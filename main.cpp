#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

int main()
{
	cout << "Hello hi, we are online" << endl;
	const unsigned int width = VideoMode::getDesktopMode().width,
					   height = VideoMode::getDesktopMode().height;
	VideoMode vm(width, height);

	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	window.setFramerateLimit(60);

	ComplexPlane plane(static_cast<int>(width), static_cast<int>(height));

	Font font;
	font.loadFromFile("fonts/IBMPlexMono-Regular.ttf");

	Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(25);
	text.setPosition(20, 20);
	text.setString("a");
	cout << "Okay we are initializing." << endl;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
			else if (event.type == Event::KeyPressed &&
					 event.key.code == Keyboard::Escape)
			{
				window.close();
			}
			else if (event.type == Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == Mouse::Left)
				{
					plane.zoomIn();
				}
				else if (event.mouseButton.button == Mouse::Right)
				{
					plane.zoomOut();
				}

				plane.setCenter({event.mouseButton.x, event.mouseButton.y});
			}
			else if (event.type == Event::MouseMoved)
			{
				plane.setMouseLocation(
					{event.mouseButton.x, event.mouseButton.y});
			}
		}
		plane.updateRender();
		plane.loadText(text);
		window.clear();
		window.draw(plane);
		window.draw(text);
		window.display();
	}
	return 0;
}