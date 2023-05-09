#pragma once
#include <memory>
#include <string>
#include <cstdlib>
#include <format>
#include "conio.h"


class Game;

class Organism {

private:
	
	char sign = ' ';

	int strength = 0;
	int initiative = 0;

	int pos_x = 1;
	int pos_y = 0;

	Game* game = nullptr;

	int _id;
	
	bool is_alive = true;

public:
	
	Organism(char sign, int strength, int initiative, int pos_x, int pos_y, Game* game) {
		static int id = 0; _id = id++;
		this->sign = sign;
		this->strength = strength;
		this->initiative = initiative;
		this->pos_x = pos_x;
		this->pos_y = pos_y;
		this->game = game;
	}

	Organism(char sign, int strength, int initiative, int pos_x, int pos_y, int _id, int is_alive, Game* game) {
		this->sign = sign;
		this->strength = strength;
		this->initiative = initiative;
		this->pos_x = pos_x;
		this->pos_y = pos_y;
		this->_id = _id;
		this->is_alive = is_alive;
		this->game = game;
	}

	char get_sign() {
		return sign;
	}

	int get_strenght() {
		return strength;
	}

	void set_strenght(int new_strenght) {
		strength = new_strenght;
	}

	int get_initiative() {
		return initiative;
	}

	void set_initiative(int new_initiative) {
		initiative = new_initiative;
	}

	int get_pos_x() {
		return pos_x;
	}

	void set_pos_x(int new_pos_x) {
		pos_x = new_pos_x;
	}

	int get_pos_y() {
		return pos_y;
	}

	void set_pos_y(int new_pos_y) {
		pos_y = new_pos_y;
	}

	Game* get_game() {
		return game;
	}

	int get_id() {
		return _id;
	}

	int get_is_alive() {
		return is_alive;
	}

	virtual std::string to_string() {

		int is_alive_as_i;
		if (is_alive) {
			is_alive_as_i = 1;
		}
		else
		{
			is_alive_as_i = 0;
		}

		return std::format("Organism(sign={},strength={},initiative={},pos_x={},pos_y={},_id={},is_alive={})", sign, strength, initiative, pos_x, pos_y, _id, is_alive_as_i);
	}

	void kill();

	bool is_empty(int delta_x, int delta_y);

	Organism* is_empty_or_ptr(int delta_x, int delta_y);

	void multiply();

	virtual bool can_block(Organism* organism) { return false; };

	virtual bool kills_when_ate(Organism* organism) { return false; };

	virtual bool gives_powerup(Organism* organism) { return false; };

	virtual void turn() = 0;
	
	virtual bool collide(std::unique_ptr<Organism>& organism) = 0;
	
	void draw(bool empty);
	
	virtual std::unique_ptr<Organism> copy() = 0;

};