#pragma once

#include "plant.h"


class Hogweed : public Plant {

public:

	Hogweed(int pos_x, int pos_y, Game* game)
		:Plant('H', 10, 0, pos_x, pos_y, 10, game) {
	}

	void kill_nearby_animals() {

		std::vector<std::pair<int, int>> deltas = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

		for (auto& delta : deltas) {

 			Organism* o = is_empty_or_ptr(delta.first, delta.second);
			if (o) {
				Plant* p = dynamic_cast<Plant*>(o);
				if (p == nullptr) {
					get_game()->kill_organism(o);
					o->draw(true);
				}
			}
		}
			
	}

	void turn() {
		multiply();
		kill_nearby_animals();
		draw(false);
	}

	bool kills_when_ate(std::unique_ptr<Organism>& organism) {
		get_game()->kill_organism(organism.get());
		get_game()->kill_organism(this);
		return true;
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Hogweed>(get_pos_x(), get_pos_y(), get_game());
	}

};