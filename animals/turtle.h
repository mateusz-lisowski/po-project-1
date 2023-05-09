#pragma once

#include <cstdlib>
#include <stdio.h>

#include "animal.h"
#include "conio.h"


class Turtle : public Animal {

public:

	Turtle(int pos_x, int pos_y, Game* game)
		:Animal('T', 2, 1, pos_x, pos_y, game) {
	}

	Turtle(int strenght, int initiative, int pos_x, int pos_y, int _id, bool is_alive, Game* game)
		:Animal('T', strenght, initiative, pos_x, pos_y, _id, is_alive, game) {
	}

	void turn() {
		move(4);
		draw(false);
	}

	bool can_block(Organism* organism) override {
		if (organism->get_strenght() < 5) {
			return true;
		}
		return false;
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Turtle>(get_pos_x(), get_pos_y(), get_game());
	}
};