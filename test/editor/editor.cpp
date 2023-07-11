//badger
#include <SFML/Graphics.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "EDITOR TEST!");

	// Create grid system
	const int gridSize = 32;
	const int gridWidth = window.getSize().x / gridSize;
	const int gridHeight = window.getSize().y / gridSize;

	std::vector<std::vector<int>> grid(gridWidth, std::vector<int>(gridHeight, 0));

	// Load level data from JSON file
	nlohmann::json levelData;

	std::ifstream levelFile("level.json");

	if (levelFile.is_open()) {
		levelFile >> levelData;
		levelFile.close();
	}
	else {
		std::cerr << "Failed to open level.json\n";
		return 1;
	}

	// Create player, platforms, and enemies from level data
	sf::RectangleShape player(sf::Vector2f(levelData["player"]["width"] * gridSize, levelData["player"]["height"] * gridSize));
	player.setFillColor(sf::Color::Green);
	player.setPosition(levelData["player"]["x"] * gridSize, levelData["player"]["y"] * gridSize);

	std::vector<sf::RectangleShape> platforms;
	for (auto& platformData : levelData["platforms"]) {
		sf::RectangleShape platform(sf::Vector2f(platformData["width"] * gridSize, platformData["height"] * gridSize));
		platform.setFillColor(sf::Color::Blue);
		platform.setPosition(platformData["x"] * gridSize, platformData["y"] * gridSize);
		platforms.push_back(platform);
	}

	std::vector<sf::RectangleShape> enemies;
	for (auto& enemyData : levelData["enemies"]) {
		sf::RectangleShape enemy(sf::Vector2f(enemyData["width"] * gridSize, enemyData["height"] * gridSize));
		enemy.setFillColor(sf::Color::Red);
		enemy.setPosition(enemyData["x"] * gridSize, enemyData["y"] * gridSize);
		   enemies.push_back(enemy);
}

// Game loop
bool gameStarted = false;
while (window.isOpen()) {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::P) {
				// Switch to platform mode
			}
			else if (event.key.code == sf::Keyboard::E) {
				// Switch to enemy mode
			}
			else if (event.key.code == sf::Keyboard::O) {
				// Switch to player mode
			}
			else if (event.key.code == sf::Keyboard::Space) {
				// Start game
				gameStarted = true;
			}
		}
		else if (event.type == sf::Event::MouseButtonPressed) {
			if (!gameStarted) {
				int x = event.mouseButton.x / gridSize;
				int y = event.mouseButton.y / gridSize;

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
					// Add platform to grid
					grid[x][y] = 1;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
					// Add enemy to grid
					grid[x][y] = 2;
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)) {
					// Move player to grid location
					player.setPosition(x * gridSize, y * gridSize);
				}
			}
		}
	}

	if (gameStarted) {
		// Update player position based on input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player.move(-gridSize, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player.move(gridSize, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			// Smoothly jump
		}

		// Update enemy positions based on time
		// Detect collisions between player, platforms, and enemies
	}

	// Clear window and draw objects
	window.clear(sf::Color::White);

	// Draw grid lines
	for (int i = 0; i <= gridWidth; i++) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(i * gridSize, 0)),
			sf::Vertex(sf::Vector2f(i * gridSize, window.getSize().y))
		};
		window.draw(line, 2, sf::Lines);
	}
	for (int i = 0; i <= gridHeight; i++) {
		sf::Vertex line[] = {
			sf::Vertex(sf::Vector2f(0, i * gridSize)),
			sf::Vertex(sf::Vector2f(window.getSize().x, i * gridSize))
		};
		window.draw(line, 2, sf::Lines);
	}

	// Draw player, platforms, and enemies
	window.draw(player);
	for (auto& platform : platforms) {
		window.draw(platform);
	}
	for (auto& enemy : enemies) {
		window.draw(enemy);
	}

	window.display();
}

// Save level data to JSON file
nlohmann::json newLevelData;

newLevelData["player"]["x"] = player.getPosition().x / gridSize;
newLevelData["player"]["y"] = player.getPosition().y / gridSize;
newLevelData["player"]["width"] = player.getSize().x / gridSize;
newLevelData["player"]["height"] = player.getSize().y / gridSize

// Loop through grid and add platforms and enemies to JSON data
for (int i = 0; i < gridWidth; i++) {
	for (int j = 0; j < gridHeight; j++) {
		if (grid[i][j] == 1) {
			// Add platform to JSON data
			int width = 1;
			while (i + width < gridWidth && grid[i + width][j] == 1) {
				width++;
			}
			newLevelData["platforms"].push_back({
				{"x", i},
				{"y", j},
				{"width", width},
				{"height", 1}
			});
		}
		else if (grid[i][j] == 2) {
			// Add enemy to JSON data
			int width = 1;
			while (i + width < gridWidth && grid[i + width][j] == 2) {
				width++;
			}
			newLevelData["enemies"].push_back({
				{"x", i},
				{"y", j},
				{"width", width},
				{"height", 1},
				{"movement_distance", 5} // example value, replace with actual value
			});
		}
	}
}

// Write JSON data to file
std::ofstream file("level.json");
file << newLevelData.dump(4);
file.close();

return 0;
}