#pragma once

class Bird
{
	bool dead;

	float vertical_speed;
	float y;

	short x;

	unsigned fitness;

	unsigned short score;

	std::uniform_int_distribution<unsigned short> mutation_distribution;


	std::uniform_real_distribution<float> node_distribution;

	std::vector<std::vector<std::vector<float>>> weights;
public:
	Bird();


	bool do_ai_stuff(std::vector<Pipes> i_pipes);
	bool get_dead();
	bool operator>(Bird& i_bird);
	bool operator<(Bird& i_bird);

	float get_gap_difference(std::vector<Pipes> i_pipes);
	float get_y();

	unsigned get_fitness();

	unsigned short get_score();

	void crossover(std::mt19937_64& i_random_engine, const std::vector<std::vector<std::vector<float>>>& i_bird_0_weights, const std::vector<std::vector<std::vector<float>>>& i_bird_1_weights);
	void draw(sf::RenderWindow& i_window);
	void generate_weights(std::mt19937_64& i_random_engine);
	void reset();

	void update(bool i_move, std::vector<Pipes> i_pipes);

	std::vector<std::vector<std::vector<float>>> get_weights();
};