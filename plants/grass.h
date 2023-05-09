#pragma once

#include "plant.h"


class Grass : public Plant {

public:

	Grass(int pos_x, int pos_y, Game* game)
		:Plant('G', 0, 0, pos_x, pos_y, 50, game) {
	}

	void turn() {
		multiply();
		draw(false);
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Grass>(get_pos_x(), get_pos_y(), get_game());
	}

};