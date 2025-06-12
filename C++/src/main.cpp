#include "../include/input.hpp"
#include "../include/main_menu.hpp"

#include "../include/modules/equation_solving.hpp"
#include "../include/modules/random_arrays.hpp"
#include "../include/modules/random_numbers.hpp"
#include "../include/modules/voting_theory.hpp"

int main() {
	while (true) {
		printMainMenu();
		int value = getValue<int>("Введите раздел программы");
		MainMenu element;
		try {
			element = convertIntToMainMenu(value);
		} catch (...) {
			continue;
		}
		switch (element) {
		case MainMenu::EQUATION_SOLVER:
			solveEquation();
			break;
		case MainMenu::RANDOM_ARRAYS:
			randomArraysActions();
			break;
		case MainMenu::RANDOM_NUMBERS:
			generateRandomNumbers();
			break;
		case MainMenu::VOTING_THEORY:
			startVote();
			break;
		case MainMenu::EXIT:
			return 0;
		}
	}
	return 0;
}
