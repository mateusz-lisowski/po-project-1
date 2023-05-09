#include "organism.h"
#include "game.h"
#include "animals/man.h"

void Organism::draw(bool empty) {
	c_gotoxy(pos_x + game->get_board_margin_x() + 2, pos_y + game->get_board_margin_y() + 1);
	if (empty) {
		printf(" ");
	}
	else
	{
		printf("%c", sign);
	}
}

bool Organism::is_empty(int delta_x, int delta_y) {

	int possible_new_x = get_pos_x() + delta_x;
	int possible_new_y = get_pos_y() + delta_y;

	bool is_empty = true;
	for (auto& o : get_game()->get_organisms()) {
		if (o->get_pos_x() == possible_new_x && o->get_pos_y() == possible_new_y) {
			is_empty = false;
			break;
		}
	}

	return is_empty;
}


Organism* Organism::is_empty_or_ptr(int delta_x, int delta_y) {

	int possible_new_x = get_pos_x() + delta_x;
	int possible_new_y = get_pos_y() + delta_y;

	bool is_empty = true;
	for (auto& o : get_game()->get_organisms()) {
		if (o->get_pos_x() == possible_new_x && o->get_pos_y() == possible_new_y) {
			return o.get();
		}
	}

	return nullptr;
}


void Organism::multiply() {

	std::unique_ptr<Organism> new_organism = copy();

	std::vector<std::pair<int, int>> deltas = { { 0, -1 }, { 1, 0 }, { 0, 1 }, { -1, 0 } };

	for (auto& delta : deltas)
		if (is_empty(delta.first, delta.second) &&
			get_pos_x() + delta.first >= 0 && get_pos_y() + delta.second >= 0 &&
			get_pos_x() + delta.first < get_game()->get_game_width() && get_pos_y() + delta.second < get_game()->get_game_height()) {

			new_organism->set_pos_x(get_pos_x() + delta.first);
			new_organism->set_pos_y(get_pos_y() + delta.second);
			get_game()->output(std::format("New organism {} created ({}, {})", new_organism->get_sign(), new_organism->get_pos_x(), new_organism->get_pos_y()).c_str());
			get_game()->add_organism(std::move(new_organism));
			break;
		}

}

void Organism::kill() {

	Man* m = dynamic_cast<Man*>(this);
	if (m != nullptr) {
		get_game()->set_is_man_alive(false);
	}

	is_alive = false;
	get_game()->output(std::format("Organism {} ({}, {}) was killed", get_sign(), get_pos_x(), get_pos_y()).c_str());
}