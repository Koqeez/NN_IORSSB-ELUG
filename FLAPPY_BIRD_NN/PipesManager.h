#pragma once

class PipesManager {
	bool temp_bool;

	unsigned short generator_timer;
	std::vector<Pipes> pipes;
public:
	PipesManager();

	void draw(sf::RenderWindow& i_window);
	void update();

	std::vector<Pipes> get_pipes();
};