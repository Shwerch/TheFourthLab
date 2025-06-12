#include "../../include/modules/random_arrays.hpp"

#include <array>
#include <iomanip>
#include <iostream>

std::minstd_rand rand_engine(std::random_device{}());
bool rand_engine_initialized = true;

void fill_random_array(std::vector<int> &arr, int min_val, int max_val) {
	std::uniform_int_distribution<> distrib(min_val, max_val);
	for (int &val : arr) {
		val = distrib(rand_engine);
	}
}

void print_vector(const std::vector<int> &arr) {
	std::cout << std::string(30, '-') << std::endl;
	for (int val : arr) {
		std::cout << val << " ";
	}
	std::cout << std::endl << std::string(30, '-') << std::endl;
}

void calculate_means(const std::vector<int> &arr, double &mean_negative, int &count_negative, double &mean_positive,
					 int &count_positive) {
	long long sum_negative = 0;
	count_negative = 0;
	long long sum_positive = 0;
	count_positive = 0;

	for (int val : arr) {
		if (val < 0) {
			sum_negative += val;
			count_negative++;
		} else if (val > 0) {
			sum_positive += val;
			count_positive++;
		}
	}

	if (count_negative > 0) {
		mean_negative = static_cast<double>(sum_negative) / count_negative;
	} else {
		mean_negative = 0.0;
	}

	if (count_positive > 0) {
		mean_positive = static_cast<double>(sum_positive) / count_positive;
	} else {
		mean_positive = 0.0;
	}
}

void swap_min_max(std::vector<int> &arr) {
	if (arr.empty()) {
		return;
	}

	ElementInfo min_info = {arr[0], 0};
	ElementInfo max_info = {arr[0], 0};

	for (size_t i = 0; i < arr.size(); ++i) {
		if (arr[i] < min_info.value) {
			min_info.value = arr[i];
			min_info.index = i;
		}
		if (arr[i] > max_info.value) {
			max_info.value = arr[i];
			max_info.index = i;
		}
	}

	if (min_info.index != max_info.index) {
		std::swap(arr[min_info.index], arr[max_info.index]);
	}
}

std::vector<int> find_decreasing_sequence(const std::vector<int> &arr) {
	std::vector<int> sequence;
	if (arr.empty()) {
		return sequence;
	}

	sequence.push_back(arr[0]);
	for (size_t i = 1; i < arr.size(); ++i) {
		if (arr[i] < sequence.back()) {
			sequence.push_back(arr[i]);
		}
	}
	return sequence;
}

void fill_special_array(std::vector<int> &arr) {
	if (arr.empty()) {
		return;
	}
	arr[0] = 1000;
	for (size_t i = 1; i < arr.size(); ++i) {
		arr[i] = arr[i - 1] + 100;
	}
}

void print_special_array(const int number) {
	std::cout << std::string(30, '-') << std::endl;
	int currentNumber = 1000;
	int increment = 100;
	std::array<int, 5> buffer;
	for (int i = 0; i < number; ++i) {
		for (int j = 0; j < 5; ++j) {
			buffer.at(j) = currentNumber;
			currentNumber += ++increment;
		}
		for (int j = 4; j >= 0; --j) {
			std::cout << buffer.at(j);
			if (j > 0) {
				std::cout << '\t';
			}
		}
		std::cout << std::endl;
	}
	std::cout << std::string(30, '-') << std::endl;
}

void randomArraysActions() {
	if (!rand_engine_initialized) {
		std::cerr << "Ошибка: Генератор случайных чисел не инициализирован." << std::endl;
		return;
	}

	int number;
	std::cout << "Введите размер массива (n >= 10): ";
	while (!(std::cin >> number) || number < 10) {
		std::cout << "Некорректный ввод. Пожалуйста, введите целое число не менее 10: ";
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	std::vector<int> arr(number);
	fill_random_array(arr, -100, 100);
	std::cout << "Исходный массив:" << std::endl;
	print_vector(arr);

	double mean_negative = 0.0;
	int count_negative = 0;
	double mean_positive = 0.0;
	int count_positive = 0;

	calculate_means(arr, mean_negative, count_negative, mean_positive, count_positive);

	if (count_negative > 0) {
		std::cout << "Среднее арифметическое отрицательных элементов: " << std::fixed << std::setprecision(2)
				  << mean_negative << std::endl;
	} else {
		std::cout << "В массиве нет отрицательных элементов." << std::endl;
	}

	if (count_positive > 0) {
		std::cout << "Среднее арифметическое положительных элементов: " << std::fixed << std::setprecision(2)
				  << mean_positive << std::endl;
	} else {
		std::cout << "В массиве нет положительных элементов." << std::endl;
	}

	swap_min_max(arr);
	std::cout << "Массив после обмена максимального и минимального элементов:" << std::endl;
	print_vector(arr);

	std::vector<int> decreasing_sequence = find_decreasing_sequence(arr);
	std::cout << "Убывающая последовательность элементов:" << std::endl;
	if (decreasing_sequence.empty()) {
		std::cout << "Убывающая последовательность не найдена." << std::endl;
	} else {
		print_vector(decreasing_sequence);
	}

	print_special_array(number);
}
