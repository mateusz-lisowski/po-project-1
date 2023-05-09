#pragma once
#include "plant.h"


class Nightshade : public Plant {

public:

	Nightshade(int pos_x, int pos_y, Game* game)
		:Plant('N', 99, 0, pos_x, pos_y, 25, game) {
	}

	void turn() {
		multiply();
		draw(false);
	}

	bool kills_when_ate(Organism* organism) override {
		get_game()->kill_organism(organism);
		get_game()->kill_organism(this);
		return true;
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Nightshade>(get_pos_x(), get_pos_y(), get_game());
	}

};