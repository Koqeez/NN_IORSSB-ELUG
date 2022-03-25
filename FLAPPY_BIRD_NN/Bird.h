#pragma once

class Bird {
	bool dead;
	float y;
	float vertical_speed;

public:
	Bird();
	void draw(sf::RenderWindow& i_window);
	void update();

	bool get_dead();
};