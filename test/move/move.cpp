//badger
#include <SFML/Graphics.hpp>
#include <cmath>

//const float GRAVITY = 9.81f;
const float GRAVITY = .000001;

int main()
{
	// Create window
	sf::RenderWindow window(sf::VideoMode(800, 600), "TEST MOVE!");

	// Create sprite
	sf::Texture texture;
	texture.loadFromFile("../player.jpg");
	sf::Sprite sprite(texture);
	sprite.setScale(.1,.1);

	// Define jump variables
	float jumpHeight = 200.f;
	float initialVelocity = std::sqrt(2 * GRAVITY * jumpHeight);
	float currentVelocity = initialVelocity;
	float time = 0.f;
	bool isJumping = false;

	// Define mass of sprite
	float mass = 10.f;

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

		// Check for collision with borders
		sf::Vector2f spritePosition = sprite.getPosition();
		if (spritePosition.x < 0)
			spritePosition.x = 0;
		else if (spritePosition.x > window.getSize().x - sprite.getGlobalBounds().width)
			spritePosition.x = window.getSize().x - sprite.getGlobalBounds().width;
		if (spritePosition.y < 0)
			spritePosition.y = 0;
		else if (spritePosition.y > window.getSize().y - sprite.getGlobalBounds().height)
		{
			spritePosition.y = window.getSize().y - sprite.getGlobalBounds().height;
			isJumping = false;
			currentVelocity = 0.f;
		}

		// Update jump
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isJumping)
		{
			isJumping = true;
			time = 0.f;
			currentVelocity = initialVelocity;
		}
		if (isJumping)
		{
			float displacement = currentVelocity * time + 0.5f * GRAVITY * time * time;
			spritePosition.y -= displacement;
			currentVelocity = initialVelocity - GRAVITY * time;
			time += 0.1f;
		}
		else
		{
			float displacement = 0.5f * GRAVITY * time * time;
			spritePosition.y += displacement;
			time += 0.1f;
		}

		// Update sprite position
		sprite.setPosition(spritePosition);

		// Clear screen and draw sprite
		window.clear();
		window.draw(sprite);
		window.display();
	}

	return 0;
}