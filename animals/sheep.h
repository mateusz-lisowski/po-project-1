#pragma once

#include <cstdlib>
#include <stdio.h>

#include "animal.h"
#include "conio.h"


class Sheep : public Animal {

public:

	Sheep(int pos_x, int pos_y, Game* game)
		:Animal('O', 4, 4, pos_x, pos_y, game) {
	}

	Sheep(int strenght, int initiative, int pos_x, int pos_y, int _id, bool is_alive, Game* game)
		:Animal('O', strenght, initiative, pos_x, pos_y, _id, is_alive, game) {
	}

	void turn() {
		move(1);
		draw(false);
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Sheep>(get_pos_x(), get_pos_y(), get_game());
	}

};