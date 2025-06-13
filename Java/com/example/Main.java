package com.example;

import com.example.menu.MainMenu;
import com.example.menu.MenuHandler;
import com.example.modules.equation.EquationSolver;
import com.example.modules.randomarrays.RandomArrays;
import com.example.modules.randomnumbers.RandomNumbers;
import com.example.modules.voting.VotingSystem;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) {
		// A single Scanner instance for the entire application
		Scanner scanner = new Scanner(System.in);

		while (true) {
			MenuHandler.printMainMenu();
			try {
				int choice = MenuHandler.getUserChoice(scanner);
				MainMenu option = MainMenu.fromInt(choice);

				switch (option) {
					case EQUATION_SOLVER -> EquationSolver.solveEquation();
					case RANDOM_ARRAYS -> RandomArrays.run(scanner);
					case RANDOM_NUMBERS -> RandomNumbers.run(scanner);
					case VOTING_THEORY -> VotingSystem.run();
					case EXIT -> {
						System.out.println("Exiting program.");
						return;
					}
				}
			} catch (IllegalArgumentException e) {
				System.out.println("Invalid choice, please try again.\n");
			}
		}
	}
}
