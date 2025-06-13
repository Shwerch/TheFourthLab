package com.example.menu;

import java.util.InputMismatchException;
import java.util.Scanner;

public final class MenuHandler {

	private MenuHandler() {}

	/**
	 * Prints the main menu to the console.
	 * Corresponds to printMainMenu .
	 */
	public static void printMainMenu() {
		System.out.println("=".repeat(50));
		System.out.println("           MAIN MENU");
		System.out.println("=".repeat(50));
		for (MainMenu item : MainMenu.values()) {
			System.out.printf(
				"[%d] %s%n",
				item.ordinal() + 1,
				item.getDescription()
			);
		}
		System.out.println();
	}

	/**
	 * Gets and validates the user's menu choice.
	 */
	public static int getUserChoice(Scanner scanner) {
		System.out.print("Введите раздел программы: "); //
		try {
			return scanner.nextInt();
		} catch (InputMismatchException e) {
			scanner.next(); // Clear the invalid input
			throw new IllegalArgumentException(
				"Invalid input. Please enter a number."
			);
		} finally {
			scanner.nextLine(); // Consume newline
		}
	}
}
