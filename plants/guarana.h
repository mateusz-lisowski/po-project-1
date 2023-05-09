#pragma once

#include "plant.h"


class Guarana : public Plant {

public:

	Guarana(int pos_x, int pos_y, Game* game)
		:Plant('X', 0, 0, pos_x, pos_y, 25, game) {
	}

	void turn() {
		multiply();
		draw(false);
	}

	bool gives_powerup(Organism* organism) override {
		organism->set_strenght(organism->get_strenght() + 3);
		get_game()->kill_organism(this);
		return true;
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Guarana>(get_pos_x(), get_pos_y(), get_game());
	}

};