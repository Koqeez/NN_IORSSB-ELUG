#pragma once

class Pipes
{
	bool direction;

	short x;

	unsigned char y_movement_timer;

	unsigned short y;
public:
	Pipes(short i_x, unsigned short i_y);

	bool get_direction();
	bool is_gone();

	short get_x();

	unsigned short get_y();

	void draw(sf::RenderWindow& i_window);
	void update();
};