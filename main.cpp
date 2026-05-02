#include <SFML/Graphics.hpp>

#include<iostream>

using namespace sf;

using namespace std;

int main()
{
	const unsigned int width = VideoMode::getDesktopMode().width, height =
		                   VideoMode::getDesktopMode().height;
	cout << "hello hi" << endl;

	VideoMode vm(width / 2, height / 2);

	RenderWindow window(vm, "Mandelbrot Set", Style::Default);

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
		window.display();
	}
	return 0;
}