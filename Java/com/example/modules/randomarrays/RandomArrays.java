package com.example.modules.randomarrays;

import com.example.consoleio.ConsoleInput;
import com.example.modules.randomarrays.records.ElementInfo;
import java.util.*;

public final class RandomArrays {

	// java.util.Random является подходящей заменой для std::minstd_rand
	private static final Random randomEngine = new Random();

	private RandomArrays() {}

	/**
	 * Заполняет массив случайными целыми числами в заданном диапазоне.
	 * Соответствует fill_random_array.
	 */
	private static void fillRandomArray(int[] arr, int minVal, int maxVal) {
		for (int i = 0; i < arr.length; i++) {
			// nextInt(bound) генерирует число от 0 до bound-1.
			// Для диапазона [min, max] формула: random.nextInt(max - min + 1) + min
			arr[i] = randomEngine.nextInt(maxVal - minVal + 1) + minVal;
		}
	}

	/**
	 * Выводит элементы массива в консоль.
	 * Соответствует print_vector.
	 */
	private static void printArray(int[] arr) {
		System.out.println("-".repeat(30));
		for (int val : arr) {
			System.out.print(val + " ");
		}
		System.out.println("\n" + "-".repeat(30));
	}

	/**
	 * Выводит элементы списка в консоль.
	 */
	private static void printList(List<Integer> list) {
		System.out.println("-".repeat(30));
		for (int val : list) {
			System.out.print(val + " ");
		}
		System.out.println("\n" + "-".repeat(30));
	}

	/**
	 * Вычисляет среднее арифметическое для положительных и отрицательных элементов.
	 * Соответствует calculate_means.
	 * @return Массив double: [mean_negative, mean_positive].
	 */
	private static double[] calculateMeans(int[] arr) {
		long sumNegative = 0;
		int countNegative = 0;
		long sumPositive = 0;
		int countPositive = 0;

		for (int val : arr) {
			if (val < 0) { //
				sumNegative += val;
				countNegative++; //
			} else if (val > 0) {
				sumPositive += val;
				countPositive++;
			}
		}

		double meanNegative = (countNegative > 0)
			? (double) sumNegative / countNegative
			: 0.0; //
		double meanPositive = (countPositive > 0)
			? (double) sumPositive / countPositive
			: 0.0; //

		return new double[] {
			meanNegative,
			meanPositive,
			countNegative,
			countPositive,
		};
	}

	/**
	 * Меняет местами минимальный и максимальный элементы в массиве.
	 * Соответствует swap_min_max.
	 */
	private static void swapMinMax(int[] arr) {
		if (arr.length == 0) return;

		ElementInfo minInfo = new ElementInfo(arr[0], 0);
		ElementInfo maxInfo = new ElementInfo(arr[0], 0);

		for (int i = 1; i < arr.length; i++) { //
			if (arr[i] < minInfo.value()) {
				minInfo = new ElementInfo(arr[i], i); //
			}
			if (arr[i] > maxInfo.value()) {
				maxInfo = new ElementInfo(arr[i], i);
			}
		}

		if (minInfo.index() != maxInfo.index()) {
			int temp = arr[minInfo.index()];
			arr[minInfo.index()] = arr[maxInfo.index()];
			arr[maxInfo.index()] = temp; //
		}
	}

	/**
	 * Находит первую убывающую подпоследовательность.
	 * Соответствует find_decreasing_sequence.
	 */
	private static List<Integer> findDecreasingSequence(int[] arr) {
		List<Integer> sequence = new ArrayList<>();
		if (arr.length == 0) return sequence;

		sequence.add(arr[0]); //
		for (int i = 1; i < arr.length; i++) {
			if (arr[i] < sequence.getLast()) { //
				sequence.add(arr[i]);
			}
		}
		return sequence; //
	}

	/**
	 * Выводит специальный массив, как в C++ коде.
	 * Соответствует print_special_array.
	 */
	private static void printSpecialArray(int n) {
		System.out.println("-".repeat(30));
		int currentNumber = 1000;
		int increment = 100;
		int[] buffer = new int[5]; //

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 5; j++) {
				buffer[j] = currentNumber;
				currentNumber += ++increment; //
			}
			for (int j = 4; j >= 0; j--) { //
				System.out.print(buffer[j] + (j > 0 ? "\t" : "")); //
			}
			System.out.println();
		}
		System.out.println("-".repeat(30)); //
	}

	/**
	 * Основной метод модуля, запускающий всю логику.
	 * Соответствует randomArraysActions.
	 */
	public static void run(Scanner scanner) {
		int number = ConsoleInput.getInt(
			scanner,
			"Введите размер массива (n >= 10): ",
			10
		); //

		int[] arr = new int[number];
		fillRandomArray(arr, -100, 100); //
		System.out.println("Исходный массив:");
		printArray(arr);

		double[] means = calculateMeans(arr); //
		double meanNegative = means[0];
		double meanPositive = means[1];
		int countNegative = (int) means[2];
		int countPositive = (int) means[3];

		if (countNegative > 0) { //
			System.out.printf(
				"Среднее арифметическое отрицательных элементов: %.2f%n",
				meanNegative
			);
		} else {
			System.out.println("В массиве нет отрицательных элементов."); //
		}
		if (countPositive > 0) { //
			System.out.printf(
				"Среднее арифметическое положительных элементов: %.2f%n",
				meanPositive
			);
		} else {
			System.out.println("В массиве нет положительных элементов.");
		}

		swapMinMax(arr); //
		System.out.println(
			"Массив после обмена максимального и минимального элементов:"
		);
		printArray(arr);

		List<Integer> decreasingSequence = findDecreasingSequence(arr); //
		System.out.println("Убывающая последовательность элементов:");
		if (decreasingSequence.size() <= 1) { // Условие изменено для более точного соответствия
			System.out.println("Убывающая последовательность не найдена.");
		} else {
			printList(decreasingSequence); //
		}

		printSpecialArray(number); //
	}
}
