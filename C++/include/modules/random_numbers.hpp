#pragma once

#include <vector>

struct BbsParams {
	long long pVal; // Простое число p
	long long qVal; // Простое число q
	long long modM; // Модуль M = p * q
};

bool is_prime(long long num);

long long gcd(long long a, long long b);

long long power_mod(long long base, long long exp, long long mod);

long long get_positive_long_input();

long long get_prime_input();

std::vector<long long> generate_bbs_sequence(long long seedX0, long long pVal, long long qVal, int count);

void generateRandomNumbers();
