#define _CRT_SECURE_NO_WARNINGS

#include "game.h"
#include "organism.h"

#include "animals/wolf.h"
#include "animals/sheep.h"
#include "animals/fox.h"
#include "animals/turtle.h"
#include "animals/antelope.h"

#include "plants/grass.h"
#include "plants/milt.h"
#include "plants/guarana.h"
#include "plants/nightshade.h"
#include "plants/hogweed.h"

#include "animals/man.h"

void Game::add_organism_from_string(const char* organism_as_str) {

	char sign;
	int strenght;
	int initiative;
	int pos_x;
	int pos_y;
	int _id;
	int is_alive_as_i;

	int p = sscanf(organism_as_str, "Organism(sign=%c,strength=%d,initiative=%d,pos_x=%d,pos_y=%d,_id=%d,is_alive=%d)", &sign, &strenght, &initiative, &pos_x, &pos_y, &_id, &is_alive_as_i);
	if (p != 7) {
		throw "ups";
	}

	bool is_alive;
	if (is_alive_as_i == 1) {
		is_alive = true;
	}
	else
	{
		is_alive = false;
	}

	switch (sign)
	{
	case 'A': 
		add_organism(std::make_unique<Antelope>(strenght, initiative, pos_x, pos_y, _id, is_alive, this));
		break;
	case 'F': 
		add_organism(std::make_unique<Fox>(strenght, initiative, pos_x, pos_y, _id, is_alive, this));
		break;
	case 'T':
		add_organism(std::make_unique<Turtle>(strenght, initiative, pos_x, pos_y, _id, is_alive, this));
		break;
	case 'W':
		add_organism(std::make_unique<Wolf>(strenght, initiative, pos_x, pos_y, _id, is_alive, this));
		break;
	case 'O':
		add_organism(std::make_unique<Sheep>(strenght, initiative, pos_x, pos_y, _id, is_alive, this));
		break;
	case 'G':
		add_organism(std::make_unique<Grass>(pos_x, pos_y, this));
		break;
	case 'X':
		add_organism(std::make_unique<Guarana>(pos_x, pos_y, this));
		break;
	case 'H':
		add_organism(std::make_unique<Hogweed>(pos_x, pos_y, this));
		break;
	case 'M':
		add_organism(std::make_unique<Milt>(pos_x, pos_y, this));
		break;
	case 'N':
		add_organism(std::make_unique<Nightshade>(pos_x, pos_y, this));
		break;
	default:
		break;
	}
}

void Game::add_man_from_string(const char* man_as_str) {

	char sign;
	int strenght;
	int initiative;
	int pos_x;
	int pos_y;
	int _id;
	int is_alive_as_i;
	int skill_counter;
	int is_skill_activated_as_i;

	int p = sscanf(man_as_str, "Organism(sign=%c,strength=%d,initiative=%d,pos_x=%d,pos_y=%d,_id=%d,is_alive=%d,skill_counter=%d,is_skill_activated=%d)", 
		&sign, &strenght, &initiative, &pos_x, &pos_y, &_id, &is_alive_as_i, &skill_counter, &is_skill_activated_as_i);
	if (p != 9) {
		throw "ups";
	}

	bool is_alive;
	if (is_alive_as_i == 1) {
		is_alive = true;
	}
	else
	{
		is_alive = false;
	}

	bool is_skill_activated;
	if (is_skill_activated_as_i == 1) {
		is_skill_activated = true;
	}
	else
	{
		is_skill_activated = false;
	}

	add_organism(std::make_unique<Man>(strenght, initiative, pos_x, pos_y, _id, is_alive, skill_counter, is_skill_activated, this));

}