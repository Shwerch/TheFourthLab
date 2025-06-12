#include "../../include/modules/random_numbers.hpp"

#include <iostream>
#include <limits>

bool is_prime(long long num) {
	if (num <= 1) {
		return false;
	}
	if (num <= 3) {
		return true;
	}
	if (num % 2 == 0 || num % 3 == 0) {
		return false;
	}
	for (long long i = 5; i * i <= num; i = i + 6) {
		if (num % i == 0 || num % (i + 2) == 0) {
			return false;
		}
	}
	return true;
}

long long gcd(long long a, long long b) {
	while (b) {
		a %= b;
		std::swap(a, b);
	}
	return a;
}

long long power_mod(long long base, long long exp, long long mod) {
	long long res = 1;
	base %= mod;
	while (exp > 0) {
		if (exp % 2 == 1) {
			res = (res * base) % mod;
		}
		base = (base * base) % mod;
		exp /= 2;
	}
	return res;
}

long long get_positive_long_input() {
	long long value;
	while (!(std::cin >> value) || value <= 0) {
		std::cout << "Некорректный ввод. Пожалуйста, введите положительное целое число: " << std::endl;
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	return value;
}

long long get_prime_input() {
	long long primeNum;
	while (true) {
		primeNum = get_positive_long_input();
		if (is_prime(primeNum)) {
			return primeNum;
		} else {
			std::cout << "Это не простое число. Пожалуйста, введите простое число: " << std::endl;
		}
	}
}

std::vector<long long> generate_bbs_sequence(long long seedX0, long long pVal, long long qVal, int count) {
	std::vector<long long> resultSeq;
	if (count <= 0) {
		return resultSeq;
	}

	long long modM = pVal * qVal;
	long long curX = (seedX0 * seedX0) % modM;

	resultSeq.push_back(curX);

	for (int i = 1; i < count; ++i) {
		curX = (curX * curX) % modM;
		resultSeq.push_back(curX);
	}
	return resultSeq;
}

void generateRandomNumbers() {
	long long pVal = 0;
	long long qVal = 0;

	std::cout << "Введите большое простое число p (p % 4 == 3): " << std::endl;
	pVal = get_prime_input();
	while (pVal % 4 != 3) {
		std::cout << "Число p не удовлетворяет условию p % 4 == 3. Пожалуйста, введите другое число: " << std::endl;
		pVal = get_prime_input();
	}

	std::cout << "Введите большое простое число q (q % 4 == 3, q != p): " << std::endl;
	qVal = get_prime_input();
	while (qVal % 4 != 3 || qVal == pVal) {
		std::cout << "Число q не удовлетворяет условию q % 4 == 3 или q равно p. Пожалуйста, введите другое число: "
				  << std::endl;
		qVal = get_prime_input();
	}

	long long modM = pVal * qVal;

	long long seedX0 = 0;
	std::cout << "Введите начальное целое число x (взаимно простое с M=" << modM << " и меньшее M): " << std::endl;
	while (true) {
		seedX0 = get_positive_long_input();
		if (gcd(seedX0, modM) == 1 && seedX0 > 1 && seedX0 < modM) {
			break;
		} else {
			std::cout
				<< "Число x должно быть взаимно простым с M, больше 1 и меньше M. Пожалуйста, введите другое число: "
				<< std::endl;
		}
	}

	int numGen = 0;
	std::cout << "Введите количество псевдослучайных чисел для генерации: " << std::endl;
	numGen = static_cast<int>(get_positive_long_input());

	std::vector<long long> randomNumbers = generate_bbs_sequence(seedX0, pVal, qVal, numGen);

	std::cout << std::endl << "Сгенерированные псевдослучайные числа (BBS):" << std::endl;
	std::cout << std::string(20, '-') << std::endl;
	for (long long num : randomNumbers) {
		std::cout << num << std::endl;
	}
	std::cout << std::string(20, '-') << std::endl;
}
