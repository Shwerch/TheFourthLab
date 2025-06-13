package com.example.modules.randomnumbers;

import com.example.consoleio.ConsoleInput;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public final class RandomNumbers {

	private RandomNumbers() {}

	/**
	 * Corresponds to generate_bbs_sequence .
	 * Uses BigInteger for all calculations to handle arbitrarily large numbers safely.
	 */
	private static List<BigInteger> generateBbsSequence(
		BigInteger seed,
		BigInteger p,
		BigInteger q,
		int count
	) {
		List<BigInteger> sequence = new ArrayList<>();
		if (count <= 0) return sequence;

		BigInteger m = p.multiply(q); //
		BigInteger currentX = seed.modPow(BigInteger.TWO, m); // x_0 = seed^2 mod M

		for (int i = 0; i < count; i++) { //
			sequence.add(currentX);
			currentX = currentX.modPow(BigInteger.TWO, m); // x_{i+1} = x_i^2 mod M
		}
		return sequence;
	}

	/**
	 * Gets a prime number from the user that satisfies p % 4 == 3.
	 * Corresponds to the input loops in generateRandomNumbers .
	 */
	private static BigInteger getBlumPrime(Scanner scanner, String message) {
		while (true) {
			BigInteger p = ConsoleInput.getPositiveBigInteger(scanner, message);
			// isProbablePrime is the standard Java way to check primality
			if (
				p.isProbablePrime(100) &&
				p.mod(BigInteger.valueOf(4)).equals(BigInteger.valueOf(3))
			) {
				return p;
			}
			System.out.println(
				"Error: Number must be a prime and satisfy p % 4 == 3."
			);
		}
	}

	public static void run(Scanner scanner) {
		BigInteger p = getBlumPrime(
			scanner,
			"Введите большое простое число p (p % 4 == 3): "
		); //
		BigInteger q;
		while (true) {
			q = getBlumPrime(
				scanner,
				"Введите большое простое число q (q % 4 == 3, q != p): "
			); //
			if (!p.equals(q)) break;
			System.out.println("Error: q cannot be equal to p.");
		}

		BigInteger m = p.multiply(q);
		System.out.printf("Модуль M = p * q = %s%n", m);

		BigInteger seed;
		while (true) {
			seed = ConsoleInput.getPositiveBigInteger(
				scanner,
				"Введите начальное целое число x (взаимно простое с M): "
			); //
			// gcd(seed, m) == 1
			if (seed.gcd(m).equals(BigInteger.ONE)) {
				break;
			}
			System.out.println("Error: Seed must be coprime with M."); //
		}

		int count = (int) ConsoleInput.getPositiveBigInteger(
			scanner,
			"Введите количество псевдослучайных чисел для генерации: "
		).longValue(); //

		List<BigInteger> randomNumbers = generateBbsSequence(seed, p, q, count); //

		System.out.println("\nСгенерированные псевдослучайные числа (BBS):"); //
		System.out.println("-".repeat(20));
		randomNumbers.forEach(System.out::println); //
		System.out.println("-".repeat(20));
	}
}
