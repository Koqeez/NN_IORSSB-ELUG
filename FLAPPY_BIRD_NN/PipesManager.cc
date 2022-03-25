#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "PipesManager.h"
#include "Pipes.h"
#include "Global.h"

PipesManager::PipesManager() :generator_timer(GENERATOR_TIMER_DURATION) {

}

void PipesManager::draw(sf::RenderWindow& i_window) {
	for (Pipes& pipe : pipes) {
		pipe.draw(i_window);
	}
}
void PipesManager::update() {
	if (0 == generator_timer) {
		generator_timer = GENERATOR_TIMER_DURATION;

		if (0 == temp_bool) {
			pipes.push_back(Pipes(SCREEN_WIDTH, 2 * BIRD_SIZE));
		}
		else {
			pipes.push_back(Pipes(SCREEN_WIDTH, SCREEN_HEIGHT - GAP_SIZE - 2 * BIRD_SIZE));
		}
		temp_bool = 1 - temp_bool;
	}
	generator_timer--;



	for (Pipes& pipe : pipes) {
		pipe.update();
	}
	for (std::vector<Pipes>::iterator i = pipes.begin(); i != pipes.end(); i++) {
		if (1 == i->is_gone()) {
			pipes.erase(i);
		}
	}
}
std::vector<Pipes> PipesManager::get_pipes()
{
	return pipes;
}