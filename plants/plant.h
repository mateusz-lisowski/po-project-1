#pragma once

#include "../organism.h"


class Plant : public Organism {
private:

	int probability_of_seed = 1;

public:

	Plant(char sign, int strength, int initiative, int pos_x, int pos_y, int probability_of_seed, Game* game)
		:Organism(sign, strength, initiative, pos_x, pos_y, game) {
		this->probability_of_seed = probability_of_seed;
	}

	void multiply() {
		int r = rand() % 100;
		if (probability_of_seed >= r) {
			Organism::multiply();
		}
	}

	bool collide(std::unique_ptr<Organism>& organism) {
		return false;
	};

};