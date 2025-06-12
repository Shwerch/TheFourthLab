#include "../../include/modules/equation_solving.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <map>

double function(double x) { return std::cos(x + 0.3) - x * x; }

double differential(double x) { return -std::sin(x + 0.3) - 2 * x; }

double phi_positive_root(double x) {
	if (std::cos(x + 0.3) < 0) {
		return NAN;
	}
	return std::sqrt(std::cos(x + 0.3));
}

double phi_negative_root(double x) {
	if (std::cos(x + 0.3) < 0) {
		return NAN;
	}
	return -std::sqrt(std::cos(x + 0.3));
}

Result solve_bisection(double a, double b, double dz, const std::string &root_name) {
	std::cout << std::endl << "Решение " << root_name << " методом половинного деления" << std::endl;
	std::cout << std::fixed << std::setprecision(6);

	if (function(a) * function(b) >= 0) {
		std::cerr << "Ошибка: Функция на концах интервала [" << a << ", " << b
				  << "] имеет одинаковый знак. Метод половинного деления неприменим." << std::endl;
		return {0.0, -1};
	}

	std::vector<BisectionStep> steps;
	int n = 0;

	std::cout << std::setw(5) << "N" << std::setw(15) << "an" << std::setw(15) << "bn" << std::setw(15) << "bn - an"
			  << std::endl;
	std::cout << std::string(50, '-') << std::endl;

	double c;
	while ((b - a) > dz) {
		c = (a + b) / 2.0;

		steps.push_back({n, a, b, b - a});

		if (function(c) == 0.0) {
			break;
		} else if (function(a) * function(c) < 0) {
			b = c;
		} else {
			a = c;
		}
		n++;
	}

	for (const auto &step : steps) {
		std::cout << std::setw(5) << step.n << std::setw(15) << step.an << std::setw(15) << step.bn << std::setw(15)
				  << step.diff << std::endl;
	}
	std::cout << std::string(50, '-') << std::endl;

	double root = (a + b) / 2.0;
	std::cout << "Найденный корень: " << root << std::endl;
	std::cout << "Количество итераций: " << n << std::endl;

	return {root, n};
}

Result solve_newton(double x0, double dz, const std::string &root_name) {
	std::cout << std::endl << "Решение " << root_name << " методом Ньютона" << std::endl;
	std::cout << std::fixed << std::setprecision(6);

	std::vector<IterationStep> steps;
	int n = 0;
	double x_curr = x0;
	double x_next;
	double diff_val;

	std::cout << std::setw(5) << "N" << std::setw(15) << "xn" << std::setw(15) << "xn+1" << std::setw(15) << "xn+1 - xn"
			  << std::endl;
	std::cout << std::string(50, '-') << std::endl;

	do {
		double f_val = function(x_curr);
		double df_val = differential(x_curr);

		if (std::fabs(df_val) < 1e-9) {
			std::cerr << "Ошибка: Производная слишком близка к нулю (" << df_val << "). Метод Ньютона неприменим."
					  << std::endl;
			return {0.0, -1};
		}

		x_next = x_curr - f_val / df_val;
		diff_val = x_next - x_curr;

		steps.push_back({n, x_curr, x_next, diff_val});

		x_curr = x_next;
		n++;
	} while (std::fabs(diff_val) >= dz && n < 100);

	for (const auto &step : steps) {
		std::cout << std::setw(5) << step.n << std::setw(15) << step.xn << std::setw(15) << step.xn_plus_1
				  << std::setw(15) << step.diff << std::endl;
	}
	std::cout << std::string(50, '-') << std::endl;

	if (n >= 100) {
		std::cerr << "Предупреждение: Метод Ньютона достиг максимального количества итераций (100) без достижения "
					 "заданной точности."
				  << std::endl;
		return {x_curr, n};
	}

	std::cout << "Найденный корень: " << x_curr << std::endl;
	std::cout << "Количество итераций: " << n << std::endl;

	return {x_curr, n};
}

Result solve_simple_iteration(double x0, double dz, const std::string &root_name,
							  std::function<double(double)> phi_func) {
	std::cout << std::endl << "Решение " << root_name << " методом простых итераций" << std::endl;
	std::cout << std::fixed << std::setprecision(6);

	std::vector<IterationStep> steps;
	int n = 0;
	double x_curr = x0;
	double x_next;
	double diff_val;

	std::cout << std::setw(5) << "N" << std::setw(15) << "xn" << std::setw(15) << "xn+1" << std::setw(15) << "xn+1 - xn"
			  << std::endl;
	std::cout << std::string(50, '-') << std::endl;

	x_next = phi_func(x_curr);
	if (std::isnan(x_next)) {
		std::cerr << "Ошибка: Функция phi(x) вернула NaN. Возможно, некорректное начальное "
					 "приближение или область определения."
				  << std::endl;
		return {0.0, -1};
	}
	diff_val = x_next - x_curr;
	steps.push_back({n, x_curr, x_next, diff_val});
	x_curr = x_next;
	n++;

	while (std::fabs(diff_val) >= dz && n < 1000) {
		x_next = phi_func(x_curr);
		if (std::isnan(x_next)) {
			std::cerr << "Ошибка: Функция phi(x) вернула NaN на итерации " << n << ". Расходимость или иная проблема."
					  << std::endl;
			return {0.0, -1};
		}
		diff_val = x_next - x_curr;
		steps.push_back({n, x_curr, x_next, diff_val});
		x_curr = x_next;
		n++;
	}

	for (const auto &step : steps) {
		std::cout << std::setw(5) << step.n << std::setw(15) << step.xn << std::setw(15) << step.xn_plus_1
				  << std::setw(15) << step.diff << std::endl;
	}
	std::cout << std::string(50, '-') << std::endl;
	if (n >= 1000) {
		std::cerr << "Предупреждение: Метод простых итераций достиг максимального количества итераций (1000) без "
					 "достижения заданной точности."
				  << std::endl;
		return {x_curr, n};
	}

	std::cout << "Найденный корень: " << x_curr << std::endl;
	std::cout << "Количество итераций: " << n << std::endl;

	return {x_curr, n};
}

void solveEquation() {
	double a1 = 0.7;
	double b1 = 0.8;
	double initial_guess1 = 0.75;

	double a2 = -1.0;
	double b2 = -0.9;
	double initial_guess2 = -0.95;

	std::map<std::string, Result> results;

	std::cout << "Отделение корней уравнения cox(x + 0.3) = x^2 (f(x) = cos(x + 0.3) - x^2 = 0)" << std::endl;
	std::cout << "Путем анализа функции и ее значений, были определены следующие интервалы для корней:" << std::endl;
	std::cout << "1. Положительный корень: [" << a1 << ", " << b1 << "] (f(" << a1 << ") = " << function(a1) << ", f("
			  << b1 << ") = " << function(b1) << ")" << std::endl;
	std::cout << "2. Отрицательный корень: [" << a2 << ", " << b2 << "] (f(" << a2 << ") = " << function(a2) << ", f("
			  << b2 << ") = " << function(b2) << ")" << std::endl;
	std::cout << "Точность уточнения: dz = " << DZ << std::endl << std::endl;

	std::cout << std::endl << std::string(50, '=') << std::endl;
	std::cout << "Уточнение ПЕРВОГО корня";
	std::cout << std::endl << std::string(50, '=') << std::endl;

	Result res_bisection1 = solve_bisection(a1, b1, DZ, "первого корня");
	results["Бисекция_Корень1"] = res_bisection1;

	Result res_newton1 = solve_newton(initial_guess1, DZ, "первого корня");
	results["Ньютон_Корень1"] = res_newton1;

	Result res_simple_iter1 = solve_simple_iteration(initial_guess1, DZ, "первого корня", phi_positive_root);
	results["Простые_Итерации_Корень1"] = res_simple_iter1;

	std::cout << std::endl << std::string(50, '=') << std::endl;
	std::cout << "Уточнение ВТОРОГО корня";
	std::cout << std::endl << std::string(50, '=') << std::endl;

	Result res_bisection2 = solve_bisection(a2, b2, DZ, "второго корня");
	results["Бисекция_Корень2"] = res_bisection2;

	Result res_newton2 = solve_newton(initial_guess2, DZ, "второго корня");
	results["Ньютон_Корень2"] = res_newton2;

	Result res_simple_iter2 = solve_simple_iteration(initial_guess2, DZ, "второго корня", phi_negative_root);
	results["Простые_Итерации_Корень2"] = res_simple_iter2;

	std::cout << std::endl << std::string(50, '=') << std::endl;
	std::cout << "Сравнение скорости сходимости методов";
	std::cout << std::endl << std::string(50, '=') << std::endl;

	std::cout << std::left << std::setw(25) << "Method" << std::setw(15) << "Root" << std::setw(15) << "Iterations"
			  << std::endl;
	std::cout << std::string(50, '-') << std::endl;

	for (const auto &entry : results) {
		std::string method_name;
		std::string root_ident;

		if (entry.first.find("Бисекция") != std::string::npos) {
			method_name = "Half division";
		} else if (entry.first.find("Ньютон") != std::string::npos) {
			method_name = "Newton's";
		} else if (entry.first.find("Простые_Итерации") != std::string::npos) {
			method_name = "Simple iterations";
		}

		if (entry.first.find("Корень1") != std::string::npos) {
			root_ident = "First";
		} else if (entry.first.find("Корень2") != std::string::npos) {
			root_ident = "Second";
		}

		std::cout << std::left << std::setw(25) << method_name << std::setw(15) << root_ident << std::setw(15)
				  << (entry.second.iterations != -1 ? std::to_string(entry.second.iterations) : "Ошибка") << std::endl;
	}
	std::cout << std::string(50, '-') << std::endl;

	std::cout << std::endl << "Выводы о скорости сходимости:" << std::endl;
	std::cout << "- Метод Ньютона обычно демонстрирует самую быструю сходимость (квадратичную), "
				 "если начальное приближение достаточно близко к корню."
			  << std::endl;
	std::cout << "- Метод простых итераций имеет линейную сходимость, скорость которой зависит от "
				 "значения производной функции phi(x)."
			  << std::endl;
	std::cout << "- Метод половинного деления имеет самую медленную, но гарантированную линейную "
				 "сходимость, поскольку он всегда сужает интервал вдвое."
			  << std::endl;
	std::cout << "Наблюдаемые результаты (количество итераций) в таблице выше подтверждают эти "
				 "теоретические утверждения, показывая, что метод Ньютона требует наименьшее количество итераций."
			  << std::endl;
}
