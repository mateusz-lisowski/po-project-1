#pragma once

#include <cstdlib>
#include <stdio.h>
#include <memory>
#include <format>
#include "animal.h"


class Wolf : public Animal {

public:

	Wolf(int pos_x, int pos_y, Game* game)
		:Animal('W', 9, 5, pos_x, pos_y, game) {

	}

	Wolf(int strenght, int initiative, int pos_x, int pos_y, int _id, bool is_alive, Game* game)
		:Animal('W', strenght, initiative, pos_x, pos_y, _id, is_alive, game) {
	}

	void turn() {
		move(1);
		draw(false);
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Wolf>(get_pos_x(), get_pos_y(), get_game());
	}

};