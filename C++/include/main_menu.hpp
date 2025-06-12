#pragma once

#include <stdexcept>
#include <string_view>

enum class MainMenu {
	EQUATION_SOLVER,
	RANDOM_ARRAYS,
	RANDOM_NUMBERS,
	VOTING_THEORY,
	EXIT,
};

constexpr int mainMenuElements = static_cast<int>(MainMenu::EXIT) + 1;

constexpr std::string_view getElementSescription(MainMenu element) {
	switch (element) {
	case MainMenu::EQUATION_SOLVER:
		return "Решение уравнения cos(x + 0.3) = x^2 с точность до dz=10^-4";
	case MainMenu::RANDOM_ARRAYS:
		return "Вычисление массивов с использованием генератора псевдослучайных чисел minstd_rand";
	case MainMenu::RANDOM_NUMBERS:
		return "Генератор псевдослучайных чисел на основе алгоритма BBS";
	case MainMenu::VOTING_THEORY:
		return "Теория голосования";
	case MainMenu::EXIT:
		return "Выход из программы";
	default:
		throw std::runtime_error("Как ты это сделал");
	}
}

MainMenu convertIntToMainMenu(int element);

void printMainMenu();
