#include <array>
#include <chrono>
#include <random>
#include <SFML/Graphics.hpp>

#include "Pipes.h"
#include "Bird.h"
#include "Global.h"

Bird::Bird() :
	mutation_distribution(0, MUTATION_PROBABILITY - 1),
	node_distribution(-1, std::nextafter(1, 2)),
	weights(2)
{
	reset();
}

bool Bird::do_ai_stuff(std::vector<Pipes> i_pipes)
{
	std::vector<std::vector<float>> neural_network(3);

	neural_network[0].resize(TOTAL_INPUT_NODES);
	neural_network[1].resize(TOTAL_HIDDEN_NODES, 0);
	neural_network[2].resize(TOTAL_OUTPUT_NODES, 0);

	neural_network[0][0] = vertical_speed;
	neural_network[0][1] = get_gap_difference(i_pipes);

	for (Pipes& a : i_pipes)
	{
		if (x < a.get_x() + 2 * BIRD_SIZE)
		{
			neural_network[0][2] = a.get_direction();

			break;
		}
	}

	for (unsigned char a = 0; a < neural_network.size() - 1; a++)
	{
		for (unsigned char b = 0; b < neural_network[1 + a].size(); b++)
		{
			for (unsigned char c = 0; c < neural_network[a].size(); c++)
			{
				neural_network[1 + a][b] += neural_network[a][c] * weights[a][c][b];
			}

			if (0 >= neural_network[1 + a][b])
			{
				neural_network[1 + a][b] = pow<float>(2, neural_network[1 + a][b]) - 1;
			}
			else
			{
				neural_network[1 + a][b] = 1 - pow<float>(2, -neural_network[1 + a][b]);
			}
		}
	}

	return 0 <= neural_network[2][0];
}

bool Bird::get_dead()
{
	return dead;
}

bool Bird::operator>(Bird& i_bird)
{
	return get_fitness() > i_bird.get_fitness();
}

bool Bird::operator<(Bird& i_bird)
{
	return get_fitness() < i_bird.get_fitness();
}

float Bird::get_gap_difference(std::vector<Pipes> i_pipes)
{
	for (Pipes& a : i_pipes)
	{
		if (x < a.get_x() + 2 * BIRD_SIZE)
		{
			return GAP_SIZE + a.get_y() - BIRD_SIZE - y;
		}
	}

	return 0;
}

float Bird::get_y()
{
	return y;
}

unsigned Bird::get_fitness()
{
	return fitness;
}

unsigned short Bird::get_score()
{
	return score;
}

void Bird::crossover(std::mt19937_64& i_random_engine, const std::vector<std::vector<std::vector<float>>>& i_bird_0_weights, const std::vector<std::vector<std::vector<float>>>& i_bird_1_weights)
{
	for (unsigned char a = 0; a < weights.size(); a++)
	{
		for (unsigned char b = 0; b < weights[a].size(); b++)
		{
			for (unsigned char c = 0; c < weights[a][b].size(); c++)
			{
				if (0 == rand() % 2)
				{
					weights[a][b][c] = i_bird_0_weights[a][b][c];
				}
				else
				{
					weights[a][b][c] = i_bird_1_weights[a][b][c];
				}

				if (0 == mutation_distribution(i_random_engine))
				{
					weights[a][b][c] = node_distribution(i_random_engine);
				}
			}
		}
	}
}

void Bird::draw(sf::RenderWindow& i_window)
{
	sf::Sprite sprite;

	sf::Texture texture;
	texture.loadFromFile("birds.png");

	sprite.setPosition(x, round(y));
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(BIRD_SIZE * (0 >= vertical_speed), BIRD_SIZE * dead, BIRD_SIZE, BIRD_SIZE));

	i_window.draw(sprite);
}

void Bird::generate_weights(std::mt19937_64& i_random_engine)
{
	weights[0].resize(TOTAL_INPUT_NODES, std::vector<float>(TOTAL_HIDDEN_NODES));
	weights[1].resize(TOTAL_HIDDEN_NODES, std::vector<float>(TOTAL_OUTPUT_NODES));

	
	for (std::vector<std::vector<float>>& layer : weights)
	{
		for (std::vector<float>& previous_node : layer)
		{
			for (float& next_node : previous_node)
			{
		
				next_node = node_distribution(i_random_engine);
			}
		}
	}
}

void Bird::reset()
{
	dead = 0;

	vertical_speed = 0;
	y = 0.5f * (GROUND_Y - BIRD_SIZE);

	x = BIRD_START_X;

	fitness = 0;

	score = 0;
}

void Bird::update(bool i_move, std::vector<Pipes> i_pipes)
{
	vertical_speed += GRAVITY;
	y += vertical_speed;

	if (0 == dead)
	{
		if (0 <= vertical_speed && 0 <= y && 1 == do_ai_stuff(i_pipes))
		{
			vertical_speed = FLAP_SPEED;
		}

		for (Pipes& a : i_pipes)
		{
			if (x < a.get_x() + 2 * BIRD_SIZE && x > a.get_x() - BIRD_SIZE)
			{
				if (y < a.get_y() || y > GAP_SIZE + a.get_y() - BIRD_SIZE)
				{
					dead = 1;

					vertical_speed = 0;
				}
			}
		
			else if (x == a.get_x() + 2 * BIRD_SIZE)
			{
				score++;
			}
		}
	}

	if (y >= GROUND_Y - BIRD_SIZE)
	{
		dead = 1;

		vertical_speed = 0;
		y = GROUND_Y - BIRD_SIZE;
	}

	if (0 == dead)
	{
		fitness += BIRD_SPEED;
	}
	else if (1 == i_move)
	{
		x = std::max(-BIRD_SIZE, x - BIRD_SPEED);
	}
}

std::vector<std::vector<std::vector<float>>> Bird::get_weights()
{
	return weights;
}