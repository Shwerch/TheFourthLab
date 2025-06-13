package com.example.menu;

public enum MainMenu {
	EQUATION_SOLVER(
		"Решение уравнения cos(x + 0.3) = x^2 с точность до dz=10^-4"
	), //
	RANDOM_ARRAYS(
		"Вычисление массивов с использованием генератора псевдослучайных чисел"
	), //
	RANDOM_NUMBERS("Генератор псевдослучайных чисел на основе алгоритма BBS"), //
	VOTING_THEORY("Теория голосования"), //
	EXIT("Выход из программы"); //

	private final String description;

	MainMenu(String description) {
		this.description = description;
	}

	public String getDescription() {
		return description;
	}

	/**
	 * Converts an integer choice to a MainMenu enum constant.
	 * Corresponds to convertIntToMainMenu .
	 */
	public static MainMenu fromInt(int choice) {
		if (choice < 1 || choice > values().length) {
			throw new IllegalArgumentException("Invalid menu option.");
		}
		return values()[choice - 1];
	}
}
