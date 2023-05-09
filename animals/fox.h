#pragma once

#include <cstdlib>
#include <stdio.h>

#include "animal.h"
#include "conio.h"


class Fox : public Animal {

public:

	Fox(int pos_x, int pos_y, Game* game)
		:Animal('F', 3, 7, pos_x, pos_y, game) {
	}

	Fox(int strenght, int initiative, int pos_x, int pos_y, int _id, bool is_alive, Game* game)
		:Animal('F', strenght, initiative, pos_x, pos_y, _id, is_alive, game) {
	}

	void move(int probability) {
		int delta_x = 0;
		int delta_y = 0;

		int curr_pos_x = get_pos_x();
		int curr_pos_y = get_pos_y();

		int r = rand() % probability;
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
				if (o->get_strenght() >= get_strenght()) {
					should_move = false;
				}
				else
				{
					should_move = collide(o);
				}			
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

	void turn() {
		move(1);
		draw(false);
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Fox>(get_pos_x(), get_pos_y(), get_game());
	}

};