#pragma once

class Pipes {
	bool direction;

	short x;

	unsigned char y_movement_timer;

	unsigned short y;
public:
	Pipes(short i_x, unsigned short i_y);

	void draw(sf::RenderWindow& i_window);
	void update();
	bool is_gone();
};