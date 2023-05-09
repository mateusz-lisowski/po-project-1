#pragma once

#include "plant.h"


class Milt : public Plant {

public:

	Milt(int pos_x, int pos_y, Game* game)
		:Plant('M', 0, 0, pos_x, pos_y, 50, game) {
	}

	void turn() {
		multiply();
		multiply();
		multiply();
		draw(false);
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Milt>(get_pos_x(), get_pos_y(), get_game());
	}

};