package com.example.consoleio;

import java.math.BigInteger;
import java.util.InputMismatchException;
import java.util.Scanner;

public final class ConsoleInput {

	// Private constructor to prevent instantiation
	private ConsoleInput() {}

	/**
	 * Gets a valid integer from the user, ensuring it meets a minimum value.
	 * Corresponds to the input loop in randomArraysActions .
	 */
	public static int getInt(Scanner scanner, String message, int minValue) {
		while (true) {
			System.out.print(message);
			try {
				int number = scanner.nextInt();
				if (number >= minValue) {
					return number;
				}
				System.out.printf(
					"Error: Please enter an integer not less than %d.%n",
					minValue
				);
			} catch (InputMismatchException e) {
				System.out.println(
					"Invalid input. Please enter a valid integer."
				);
				scanner.next(); // Clear invalid input
			}
		}
	}

	/**
	 * Gets a positive BigInteger from the user.
	 * Corresponds to get_positive_long_input, but uses BigInteger for safety .
	 */
	public static BigInteger getPositiveBigInteger(
		Scanner scanner,
		String message
	) {
		while (true) {
			System.out.print(message);
			String input = scanner.next();
			try {
				BigInteger value = new BigInteger(input);
				if (value.signum() > 0) {
					return value;
				}
				System.out.println("Error: Please enter a positive integer.");
			} catch (NumberFormatException e) {
				System.out.println(
					"Invalid input. Please enter a valid integer."
				);
			}
		}
	}
}
