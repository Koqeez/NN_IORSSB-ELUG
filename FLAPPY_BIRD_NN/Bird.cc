#include <chrono>
#include <SFML/Graphics.hpp>

#include "Bird.h"
#include "Global.h"

Bird::Bird() : y(0.5f * (SCREEN_HEIGHT - BIRD_SIZE)),vertical_speed(0),dead(0) {

};
void Bird::draw(sf::RenderWindow& i_window) {
	sf::Sprite sprite;
	sf::Texture texture;
	texture.loadFromFile("birds.png");
	sprite.setPosition(BIRD_START_X, round(y));
	sprite.setTexture(texture);

	sprite.setTextureRect(sf::IntRect(BIRD_SIZE * (0 >= vertical_speed), BIRD_SIZE * dead, BIRD_SIZE, BIRD_SIZE));

	i_window.draw(sprite);
}
void Bird::update() {
	if (y >= SCREEN_HEIGHT - BIRD_SIZE) {
		dead = 1;
		vertical_speed = 0;
		y = SCREEN_HEIGHT - BIRD_SIZE;
	}
	else {
		vertical_speed += GRAVITY;
	}
	if (0==dead && 0<= vertical_speed && 0<=y && 1 == sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		vertical_speed = FLAP_SPEED;
	}
	y += vertical_speed;
}
bool Bird::get_dead()
{
	return dead;
}