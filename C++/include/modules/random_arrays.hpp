#pragma once

#include <random>
#include <vector>

extern std::minstd_rand rand_engine;
extern bool rand_engine_initialized;

struct ElementInfo {
	int value;
	size_t index;
};

void fill_random_array(std::vector<int> &arr, int min_val, int max_val);

void print_vector(const std::vector<int> &arr);

void calculate_means(const std::vector<int> &arr, double &mean_negative, int &count_negative, double &mean_positive,
					 int &count_positive);

void swap_min_max(std::vector<int> &arr);

std::vector<int> find_decreasing_sequence(const std::vector<int> &arr);

void fill_special_array(std::vector<int> &arr);

void print_special_array(const int number);

void randomArraysActions();
