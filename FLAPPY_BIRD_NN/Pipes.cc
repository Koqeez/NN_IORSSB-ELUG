#include <chrono>
#include <SFML/Graphics.hpp>

#include "Global.h"
#include "Pipes.h"

Pipes::Pipes(short i_x, unsigned short i_y) :direction(rand()%2), y_movement_timer(PIPE_SPEED), x(i_x), y(i_y) {

}
bool Pipes::is_gone() {
	return x <= -2 * BIRD_SIZE;
}

void Pipes::draw(sf::RenderWindow& i_window) {
	sf::Sprite sprite;

	sf::Texture texture;
	texture.loadFromFile("Pipes.png");
	sprite.setPosition(x, static_cast<float>(y - SCREEN_HEIGHT));
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(2 * BIRD_SIZE, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));

	i_window.draw(sprite);

	sprite.setPosition(x, static_cast<float>(GAP_SIZE + y));
	sprite.setTextureRect(sf::IntRect(0, 0, 2 * BIRD_SIZE, SCREEN_HEIGHT));

	i_window.draw(sprite);
}
void Pipes::update()
{
	x -= BIRD_SPEED;

	if (PIPE_INDENT == y)
	{
		direction = 1;
	}
	else if (y == GROUND_Y - GAP_SIZE - PIPE_INDENT)
	{
		direction = 0;
	}

	if (0 == y_movement_timer)
	{
		y_movement_timer = PIPE_SPEED;

		if (0 == direction)
		{
			y--;
		}
		else
		{
			y++;
		}
	}
	else
	{
		y_movement_timer--;
	}
}