#pragma once

#include <cstdlib>
#include <stdio.h>					
#include <memory>

#include "animal.h"
#include "conio.h"


class Antelope : public Animal {

public:

	Antelope(int pos_x, int pos_y, Game* game)
		:Animal('A', 4, 4, pos_x, pos_y, game) {
	}

	Antelope(int strenght, int initiative, int pos_x, int pos_y, int _id, bool is_alive, Game* game)
		:Animal('A', strenght, initiative, pos_x, pos_y, _id, is_alive, game) {
	}

	void move() {
  		int delta_x = 0;
		int delta_y = 0;

		int curr_pos_x = get_pos_x();
		int curr_pos_y = get_pos_y();

		int rx1 = rand() % 3;
		int rx2 = rand() % 2;
		
		if (rx1 == 0) {
			delta_x = 1;
		}
		
		if (rx1 == 1) {
			delta_x = 2;
		}

		if (rx2 == 0) {
			delta_x *= -1;
		}

		int ry1 = rand() % 3;
		int ry2 = rand() % 2;

		if (ry1 == 0) {
			delta_y = 1;
		}

		if (ry1 == 1) {
			delta_y = 2;
		}

		if (ry2 == 0) {
			delta_y *= -1;
		}

		int new_pos_x = curr_pos_x + delta_x;
		int new_pos_y = curr_pos_y + delta_y;

		if (new_pos_x < 0) {
			new_pos_x = curr_pos_x;
		}

		if (new_pos_y < 0) {
			new_pos_y = curr_pos_y;
		}

		if (new_pos_x >= get_game()->get_game_width()) {
			new_pos_x = curr_pos_x;
		}

		if (new_pos_y >= get_game()->get_game_height()) {
			new_pos_y = curr_pos_y;
		}
		
		bool should_move = true;
		for (auto& o : get_game()->get_organisms()) {
			if (o->get_pos_x() == new_pos_x && o->get_pos_y() == new_pos_y && o->get_id() != get_id()) {
				int random = rand() % 2;
				if (rand == 0 && o->get_sign() != 'A') {
					move();
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
		move();
		draw(false);
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Antelope>(get_pos_x(), get_pos_y(), get_game());
	}

};