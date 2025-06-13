package com.example.modules.equation;

import com.example.modules.equation.records.BisectionStep;
import com.example.modules.equation.records.IterationStep;
import com.example.modules.equation.records.Result;
import java.util.ArrayList;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;
import java.util.function.DoubleFunction;

public final class EquationSolver {

	private static final double DZ = 1e-4; //

	private EquationSolver() {}

	/**
	 * Решение методом половинного деления (Bisection).
	 */
	private static Result solveBisection(double a, double b, String rootName) {
		System.out.printf(
			"%nРешение %s методом половинного деления%n",
			rootName
		);
		if (EquationUtils.function(a) * EquationUtils.function(b) >= 0) {
			System.err.printf(
				"Ошибка: Функция на концах интервала [%.2f, %.2f] имеет одинаковый знак.%n",
				a,
				b
			);
			return new Result(Double.NaN, -1);
		}

		List<BisectionStep> steps = new ArrayList<>();
		int n = 0;
		double c;

		while ((b - a) > DZ) { //
			c = (a + b) / 2.0;
			steps.add(new BisectionStep(n, a, b, b - a)); //

			if (EquationUtils.function(c) == 0.0) {
				break;
			} else if (
				EquationUtils.function(a) * EquationUtils.function(c) < 0
			) {
				b = c; //
			} else {
				a = c; //
			}
			n++;
		}

		System.out.printf("%5s %15s %15s %15s%n", "N", "an", "bn", "bn - an");
		System.out.println("-".repeat(50));
		for (BisectionStep step : steps) {
			System.out.printf(
				"%5d %15.6f %15.6f %15.6f%n",
				step.n(),
				step.an(),
				step.bn(),
				step.diff()
			);
		}
		System.out.println("-".repeat(50));

		double root = (a + b) / 2.0;
		System.out.printf("Найденный корень: %.6f%n", root);
		System.out.printf("Количество итераций: %d%n", n);
		return new Result(root, n); //
	}

	/**
	 * Решение методом Ньютона.
	 */
	private static Result solveNewton(double x0, String rootName) {
		System.out.printf("%nРешение %s методом Ньютона%n", rootName);
		List<IterationStep> steps = new ArrayList<>();
		int n = 0;
		double xCurr = x0;

		while (n < 100) {
			double fVal = EquationUtils.function(xCurr);
			double dfVal = EquationUtils.differential(xCurr);
			if (Math.abs(dfVal) < 1e-9) { //
				System.err.println(
					"Ошибка: Производная слишком близка к нулю."
				);
				return new Result(Double.NaN, -1);
			}
			double xNext = xCurr - fVal / dfVal; //
			double diff = xNext - xCurr;
			steps.add(new IterationStep(n, xCurr, xNext, diff)); //

			xCurr = xNext;
			n++;
			if (Math.abs(diff) < DZ) break; //
		}

		System.out.printf(
			"%5s %15s %15s %15s%n",
			"N",
			"xn",
			"xn+1",
			"xn+1 - xn"
		);
		System.out.println("-".repeat(50));
		for (IterationStep step : steps) {
			System.out.printf(
				"%5d %15.6f %15.6f %15.6f%n",
				step.n(),
				step.xn(),
				step.xn_plus_1(),
				step.diff()
			);
		}
		System.out.println("-".repeat(50));

		System.out.printf("Найденный корень: %.6f%n", xCurr); //
		System.out.printf("Количество итераций: %d%n", n); //
		return new Result(xCurr, n);
	}

	/**
	 * Решение методом простых итераций.
	 */
	private static Result solveSimpleIteration(
		double x0,
		String rootName,
		DoubleFunction<Double> phiFunc
	) {
		System.out.printf("%nРешение %s методом простых итераций%n", rootName);
		List<IterationStep> steps = new ArrayList<>();
		int n = 0;
		double xCurr = x0;

		while (n < 1000) {
			double xNext = phiFunc.apply(xCurr);
			if (Double.isNaN(xNext)) { //
				System.err.println("Ошибка: Функция phi(x) вернула NaN.");
				return new Result(Double.NaN, -1);
			}
			double diff = xNext - xCurr;
			steps.add(new IterationStep(n, xCurr, xNext, diff)); //

			xCurr = xNext;
			n++;
			if (Math.abs(diff) < DZ) break; //
		}

		System.out.printf(
			"%5s %15s %15s %15s%n",
			"N",
			"xn",
			"xn+1",
			"xn+1 - xn"
		);
		System.out.println("-".repeat(50));
		for (IterationStep step : steps) {
			System.out.printf(
				"%5d %15.6f %15.6f %15.6f%n",
				step.n(),
				step.xn(),
				step.xn_plus_1(),
				step.diff()
			);
		}
		System.out.println("-".repeat(50));

		System.out.printf("Найденный корень: %.6f%n", xCurr); //
		System.out.printf("Количество итераций: %d%n", n); //
		return new Result(xCurr, n);
	}

	public static void solveEquation() {
		double a1 = 0.7, b1 = 0.8, initial_guess1 = 0.75;
		double a2 = -1.0, b2 = -0.9, initial_guess2 = -0.95;
		Map<String, Result> results = new LinkedHashMap<>();

		System.out.println(
			"\n" +
			"=".repeat(50) +
			"\nУточнение ПЕРВОГО корня\n" +
			"=".repeat(50)
		);
		results.put("Bisection_Root1", solveBisection(a1, b1, "первого корня"));
		results.put(
			"Newton_Root1",
			solveNewton(initial_guess1, "первого корня")
		);
		results.put(
			"SimpleIteration_Root1",
			solveSimpleIteration(
				initial_guess1,
				"первого корня",
				EquationUtils::phi_positive_root
			)
		);

		System.out.println(
			"\n" +
			"=".repeat(50) +
			"\nУточнение ВТОРОГО корня\n" +
			"=".repeat(50)
		);
		results.put("Bisection_Root2", solveBisection(a2, b2, "второго корня"));
		results.put(
			"Newton_Root2",
			solveNewton(initial_guess2, "второго корня")
		);
		results.put(
			"SimpleIteration_Root2",
			solveSimpleIteration(
				initial_guess2,
				"второго корня",
				EquationUtils::phi_negative_root
			)
		);

		printComparison(results);
	}

	private static void printComparison(Map<String, Result> results) {
		// ... (этот метод можно оставить без изменений)
		System.out.println(
			"\n" +
			"=".repeat(50) +
			"\nСравнение скорости сходимости методов\n" +
			"=".repeat(50)
		);
		System.out.printf(
			"%-25s %-15s %-15s%n",
			"Method",
			"Root",
			"Iterations"
		);
		System.out.println("-".repeat(55));
		for (Map.Entry<String, Result> entry : results.entrySet()) {
			String[] parts = entry.getKey().split("_");
			String methodName =
				switch (parts[0]) {
					case "Bisection" -> "Half division";
					case "Newton" -> "Newton's";
					case "SimpleIteration" -> "Simple iterations";
					default -> "Unknown";
				};
			String rootIdent = parts[1].equals("Root1") ? "First" : "Second";
			String iterations = entry.getValue().iterations() != -1
				? String.valueOf(entry.getValue().iterations())
				: "Error";
			System.out.printf(
				"%-25s %-15s %-15s%n",
				methodName,
				rootIdent,
				iterations
			);
		}
	}
}
