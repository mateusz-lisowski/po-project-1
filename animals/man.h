#pragma once

#include <cstdlib>
#include <stdio.h>

#include "animal.h"
#include "conio.h"


class Man : public Animal {

private:

	int skill_counter = 10;
	bool is_skill_active = false;

public:

	Man(int pos_x, int pos_y, Game* game)
		:Animal('Y', 5, 4, pos_x, pos_y, game) {

	}

	Man(int strenght, int initiative, int pos_x, int pos_y, int _id, bool is_alive, int skill_counter, int is_skill_active, Game* game)
		:Animal('Y', strenght, initiative, pos_x, pos_y, _id, is_alive, game) {
		this->skill_counter = skill_counter;
		this->is_skill_active = is_skill_active;
	}

	std::string to_string() {

		int is_skill_activated_as_i;
		if (is_skill_active) {
			is_skill_activated_as_i = 1;
		}
		else
		{
			is_skill_activated_as_i = 0;
		}

		return std::format("Organism(sign={},strength={},initiative={},pos_x={},pos_y={},_id={},is_alive={},skill_counter={},is_skill_activated={})", 
			get_sign(), get_strenght(), get_initiative(), get_pos_x(), get_pos_y(), get_id(), get_is_alive(), skill_counter, is_skill_activated_as_i);
	}

	void active_sklill() {
		if (!is_skill_active) {
			is_skill_active = true;
		}
	}

	void move(int delta_x, int delta_y) {
	
		int curr_pos_x = get_pos_x();
		int curr_pos_y = get_pos_y();

		int new_pos_x = curr_pos_x + delta_x;
		int new_pos_y = curr_pos_y + delta_y;

		if (new_pos_x < 0) {
			new_pos_x += 1;
		}

		if (new_pos_y < 0) {
			new_pos_y += 1;
		}

		if (new_pos_x > get_game()->get_game_width() - 1) {
			new_pos_x -= 1;
		}

		if (new_pos_y >= get_game()->get_game_height()) {
			new_pos_y -= 1;
		}

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

	void turn() {

		// Move up
		if (get_game()->get_man_move() == 1) {
			move(0, -1);
		}

		// Move right
		if (get_game()->get_man_move() == 2) {
			move(1, 0);
		}

		// Move down
		if (get_game()->get_man_move() == 3) {
			move(0, 1);
		}

		// Move left
		if (get_game()->get_man_move() == 4) {
			move(-1, 0);
		}

		// Super skill
		if (get_game()->get_man_move() == 5) {
			if (!is_skill_active) {
				is_skill_active = true;
			}
		}

		if (is_skill_active == true) {
			
			if (skill_counter >= 5) {
				set_strenght(skill_counter);
				skill_counter--;
			}

			if (skill_counter < 5) {
				skill_counter--;
			}

			if (skill_counter <= 0) {
				skill_counter = 10;
				is_skill_active = false;
			}

		}

		draw(false);
	}

	void draw(bool is_empty) {
		Organism::draw(is_empty);
		c_gotoxy(2, get_game()->get_game_height() + 6);
		printf("               ");
		c_gotoxy(2, get_game()->get_game_height() + 6);
		printf(std::format("Man's strength: {}   ", get_strenght()).c_str());
		c_gotoxy(2, get_game()->get_game_height() + 7);
		if (is_skill_active) {
			printf("Skill cannot be activated!   ");
		}
		else
		{
			printf("Skill can be activated!    ");
		}
		c_gotoxy(2, get_game()->get_game_height() + 8);
		printf(std::format("Time to next skill activation: {} ", skill_counter).c_str());
	}

	std::unique_ptr<Organism> copy() {
		return std::make_unique<Man>(get_pos_x(), get_pos_y(), get_game());
	}

};