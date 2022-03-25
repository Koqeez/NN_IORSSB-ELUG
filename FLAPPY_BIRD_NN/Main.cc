#include <array>
#include <chrono>
#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Bird.h"
#include "Pipes.h"
#include "PipesManager.h"

int main() {

	std::chrono::microseconds lag(0);

	std::chrono::steady_clock::time_point previous_time;

	unsigned short game_speed = 1;

	sf::RenderWindow window(sf::VideoMode(2 * SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "FLAPPY BIRD", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, 2 * SCREEN_WIDTH, SCREEN_HEIGHT)));

	sf::Event event;

	sf::Sprite background_sprite;
	sf::Sprite ground_sprite;

	sf::Texture background_texture;
	background_texture.loadFromFile("background.png");

	sf::Texture ground_texture;
	ground_texture.loadFromFile("ground.png");

	background_sprite.setTexture(background_texture);

	ground_sprite.setTexture(ground_texture);
	ground_sprite.setPosition(0, GROUND_Y);

	PipesManager pipes_manager;

	srand(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));

	Bird bird;

	previous_time = std::chrono::steady_clock::now();

	while (1 == window.isOpen()) {

		std::chrono::microseconds delta_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time);

		lag += delta_time;

		previous_time += delta_time;
		while (FRAME_DURATION <= lag)
		{
			lag -= FRAME_DURATION;

			while (1 == window.pollEvent(event)) {
				switch (event.type) {
				case sf::Event::Closed: {
					window.close();
				}
				}
			}

			for (unsigned short i = 0; i < game_speed; i++) {
				bool restart = 1;
				if (0 == bird.get_dead())
				{
					restart = 0;

					break;
				}
				if (0 == restart)
				{
					pipes_manager.update();
					bird.update();
				}
			}


			if (FRAME_DURATION > lag)
			{
				window.clear();
				window.draw(background_sprite);
				pipes_manager.draw(window);
				bird.draw(window);
				window.draw(ground_sprite);
				window.display();
			}
		}
	}
}