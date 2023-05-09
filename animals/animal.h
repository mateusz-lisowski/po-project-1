#pragma once
#include <iostream>
#include "../organism.h"
#include "../game.h"

class Animal : public Organism {

public:

	Animal(char sign, int strength, int initiative, int pos_x, int pos_y, Game* game)
		:Organism(sign, strength, initiative, pos_x, pos_y, game) {

	}

	Animal(char sign, int strength, int initiative, int pos_x, int pos_y, int _id, bool is_alive, Game* game)
		:Organism(sign, strength, initiative, pos_x, pos_y, _id, is_alive, game) {

	}

	void move(int probability) {
		int delta_x = 0;
		int delta_y = 0;

		int curr_pos_x = get_pos_x();
		int curr_pos_y = get_pos_y();

		int r = rand() % (4 * probability);
		if (r == 0) {
			delta_x = 1;
		}
		else if (r == 1) {
			delta_x = -1;
		}
		else if (r == 2) {
			delta_y = 1;
		}
		else if (r == 3) {
			delta_y = -1;
		}

		if (curr_pos_x <= 0) {
			delta_x += 1;
		}

		if (curr_pos_y <= 0) {
			delta_y += 1;
		}

		if (curr_pos_x >= get_game()->get_game_width() - 1) {
			delta_x -= 1;
		}

		if (curr_pos_y >= get_game()->get_game_height() - 1) {
			delta_y -= 1;
		}

		int new_pos_x = curr_pos_x + delta_x;
		int new_pos_y = curr_pos_y + delta_y;

		bool should_move = true;
		for (auto& o : get_game()->get_organisms()) {
			if (o->get_pos_x() == new_pos_x && o->get_pos_y() == new_pos_y && o->get_id() != get_id()) {
				should_move = collide(o);
				break;
			}
		}
		if (should_move) {
			draw(true);
			set_pos_x(new_pos_x);
			set_pos_y(new_pos_y);
			draw(false);
		}
	}

	bool collide(std::unique_ptr<Organism>& organism) {

		if (organism->get_sign() == get_sign()) {
			multiply();
			return false;
		}

		if (organism->can_block(this)) {
			return false;
		}

		if (organism->kills_when_ate(this)) {
			return false;
		}

		if (organism->gives_powerup(this)) {
			return true;
		}

		if (organism->get_strenght() <= get_strenght()) {
			get_game()->kill_organism(organism.get());
			return true;
		}

		if (!(organism->get_strenght() <= get_strenght())) {
			get_game()->kill_organism(this);
			return false;
		}

		return true;
	}
};