#pragma once
#include <stdio.h>
#include <vector>
#include <memory>
#include <format>
#include <fstream>
#include <string>

#include "organism.h"

class Game {

private:
	
	int game_height = 20;
	int game_width = 60;

	int board_margin_x = 2;
	int board_margin_y = 2;

	std::vector<std::unique_ptr<Organism>> organisms;

	int y = board_margin_y;
	int game_lifetime = 0;

	int man_move = 0;

	bool is_man_alive = true;

public:

	Game() {}

	Game(int game_height, int game_width, int board_margin_x, int board_margin_y) {
		this->game_width = game_height;
		this->game_height = game_width;
		this->board_margin_x = board_margin_x;
		this->board_margin_y = board_margin_y;
	}

	int get_game_height() {
		return game_height;
	}

	int get_game_width() {
		return game_width;
	}

	int get_board_margin_x() {
		return board_margin_y;
	}

	int get_board_margin_y() {
		return board_margin_y;
	}

	int get_man_move() {
		return man_move;
	}

	void set_man_move(int new_man_move) {
		man_move = new_man_move;
	}

	void set_is_man_alive(bool v) {
		is_man_alive = v;
	}

	void clear_board() {
		for (int i = 0; i < game_height; i++) {
			for (int j = 0; j < game_width; j++) {
				c_gotoxy(j + get_board_margin_x() + 2, i + get_board_margin_y() + 1);
				printf(" ");
			}
		}
	}

	void add_organism_from_string(const char* organism_as_str);

	void add_man_from_string(const char* man_as_str);

	void save() {

		if (is_man_alive) {
			std::ofstream file("save.txt");

			for (auto& o : organisms) {
				if (o->get_sign() == 'Y') {
					std::string man_as_string = o->to_string();
					file << man_as_string << '\n';
				}
			}

			for (auto& o : organisms) {
				if (o->get_sign() != 'Y') {
					std::string o_as_string = o->to_string();
					file << o_as_string << '\n';
				}
			}
			output("Game has been saved");
		}
		else
		{
			output("Game cannot be saved without man");
		}

		
	}

	void load() {

		clear_board();
	
		organisms = std::vector<std::unique_ptr<Organism>>();

		std::ifstream file("save.txt");

		std::string line;
		std::getline(file, line);
		add_man_from_string(line.c_str());

		while (std::getline(file, line)) {
			add_organism_from_string(line.c_str());
		}

		draw_game();
		output("Game has been loaded");
	}

	std::vector<std::unique_ptr<Organism>>& get_organisms() {
		return organisms;
	}

	void draw_all_organisms() {
		for (auto& o : organisms) {
			o->draw(false);
		}
	}

	void add_organism(std::unique_ptr<Organism>&& o) {
		organisms.push_back(std::move(o));
	}

	void kill_organism(Organism* o) {
		o->kill();
	}

	void next_turn() {

		game_lifetime++;

		std::vector<Organism*> tmp;
		for (auto& o : organisms) {
			tmp.push_back(o.get());
		}
		std::stable_sort(tmp.begin(), tmp.end(), [](auto& l, auto& r) { return l->get_initiative() > r->get_initiative(); });

		for (auto& o : tmp) {
			if (o->get_is_alive()) {
				o->turn();
			}
		}

		organisms.erase(std::remove_if(organisms.begin(), organisms.end(), [](auto& o) { return !o->get_is_alive(); }), organisms.end());	
		draw_all_organisms();
	}

	void draw_board(int x, int y, int margin_x, int margin_y) {
		
		x += 1;
		y += 1;
		margin_x += 1;

		c_gotoxy(margin_x, margin_y);
		for (int i = 0; i <= x; i++) {
			printf("-");
		}
		printf("\n");

		for (int j = 1; j < y; j++) {
			c_gotoxy(margin_x, margin_y + j);
			printf("|");
			c_gotoxy(margin_x + x, margin_y + j);
			printf("|");
		}
		printf("\n");

		c_gotoxy(margin_x, margin_y + y);
		for (int i = 0; i <= x; i++) {
			printf("-");
		}
	}

	void output(const char* string) {

		c_gotoxy(game_width + board_margin_x + 10, y);
		
		for (int i = 0; i < 50; i++) {
			printf(" ");
		}

		c_gotoxy(game_width + board_margin_x + 10, y);

		printf(std::format("{} -> ", game_lifetime).c_str());
		printf(string);
		y++;

		if (y > game_height) {
			y = board_margin_y;
		}
	}

	void draw_organisms() {
		for (auto& o : organisms) {
			o->draw(false);
		}
		
	}

	void draw_game() {

		draw_organisms();

		c_gotoxy(1, 0);
		printf("Mateusz Lisowski 193396");
		draw_board(game_width, game_height, board_margin_x, board_margin_y);
		
	}

};