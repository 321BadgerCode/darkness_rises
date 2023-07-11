//badger
#include <SFML/Graphics.hpp>

int main()
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");

	// Create rectangle
	sf::RectangleShape rect(sf::Vector2f(50, 30));
	rect.setFillColor(sf::Color::Red);
	rect.setPosition(100, 100);

	// Define velocity
	sf::Vector2f velocity(100,50);

	// Game loop
	while (window.isOpen())
	{
		// Handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Update rectangle position
		sf::Vector2f rectPosition = rect.getPosition();
		rectPosition += velocity * 0.01f;

		// Check for collision with screen borders
		if (rectPosition.x < 0)
		{
			rectPosition.x = 0;
			velocity.x = -velocity.x;
		}
		else if (rectPosition.x > window.getSize().x - rect.getSize().x)
		{
			rectPosition.x = window.getSize().x - rect.getSize().x;
			velocity.x = -velocity.x;
		}
		if (rectPosition.y < 0)
		{
			rectPosition.y = 0;
			velocity.y = -velocity.y;
		}
		else if (rectPosition.y > window.getSize().y - rect.getSize().y)
		{
			rectPosition.y = window.getSize().y - rect.getSize().y;
			velocity.y = -velocity.y;
		}

		// Update rectangle position and draw it
		rect.setPosition(rectPosition);
		window.clear();
		window.draw(rect);
		window.display();
	}

	return 0;
}