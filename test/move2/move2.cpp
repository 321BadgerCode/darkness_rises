//badger
#include <SFML/Graphics.hpp>

int main()
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML");

	// Create sprite
	sf::Texture texture;
	texture.loadFromFile("../player.jpg");
	sf::Sprite sprite(texture);
	sprite.setPosition(100, 100);
	sprite.setScale(.1,.1);

	// Define gravity
	const float GRAVITY = 9.8;

	// Define velocity and jump velocity
	sf::Vector2f velocity(0, 0);
	const float JUMP_VELOCITY = -50;
	const float speed=.2;

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

		// Handle keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			sprite.move(-speed,0);
			if (sprite.getPosition().x < 0)
				sprite.setPosition(0, sprite.getPosition().y);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			sprite.move(speed,0);
			if (sprite.getPosition().x > window.getSize().x - sprite.getGlobalBounds().width)
				sprite.setPosition(window.getSize().x - sprite.getGlobalBounds().width, sprite.getPosition().y);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocity.y == 0)
		{
			velocity.y = JUMP_VELOCITY;
		}

		// Update sprite position and velocity
		sf::Vector2f position = sprite.getPosition();
		position += velocity * 0.01f;
		if (position.y > window.getSize().y - sprite.getGlobalBounds().height)
		{
			position.y = window.getSize().y - sprite.getGlobalBounds().height;
			velocity.y = 0;
		}
		else
		{
			velocity.y += GRAVITY * 0.01f;
		}
		sprite.setPosition(position);

		// Draw sprite on screen
		window.clear(sf::Color::White);
		window.draw(sprite);
		window.display();
	}

	return 0;
}