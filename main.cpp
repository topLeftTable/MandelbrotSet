#include "ComplexPlane.h"
#include <SFML/Graphics.hpp>
#include<iostream>

using namespace sf;
using namespace std;

int main()
{
	const unsigned int width = VideoMode::getDesktopMode().width / 2, height =
		                   VideoMode::getDesktopMode().height / 2;
	cout << "hello hi" << endl;

	VideoMode vm(width, height);

	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

	ComplexPlane plane(static_cast<int>(width), static_cast<int>(height));

	Font font;
	font.loadFromFile("fonts/IBMPlexMono-Regular.ttf");

	Text text;
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(25);
	text.setPosition(20, 20);
	text.setString("Test message");

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
			}
		}
		window.draw(text);
		window.display();
	}
	return 0;
}