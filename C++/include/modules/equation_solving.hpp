#pragma once

#include <functional>
#include <string>

#define DZ 1e-4

struct Result {
	double root;
	int iterations;
};

struct BisectionStep {
	int n;
	double an;
	double bn;
	double diff;
};

struct IterationStep {
	int n;
	double xn;
	double xn_plus_1;
	double diff;
};

double function(double x);

double differential(double x);

double phi_positive_root(double x);

double phi_negative_root(double x);

Result solve_bisection(double a, double b, double dz, const std::string &root_name);

Result solve_newton(double x0, double dz, const std::string &root_name);

Result solve_simple_iteration(double x0, double dz, const std::string &root_name,
							  std::function<double(double)> phi_func);

void solveEquation();
