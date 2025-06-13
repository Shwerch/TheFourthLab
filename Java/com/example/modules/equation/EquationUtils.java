package com.example.modules.equation;

public final class EquationUtils {

	private EquationUtils() {}

	// f(x) = cos(x + 0.3) - x^2
	public static double function(double x) {
		return Math.cos(x + 0.3) - x * x;
	}

	// f'(x) = -sin(x + 0.3) - 2x
	public static double differential(double x) {
		return -Math.sin(x + 0.3) - 2 * x;
	}

	// phi(x) = sqrt(cos(x + 0.3)) for the positive root
	public static double phi_positive_root(double x) {
		double cosVal = Math.cos(x + 0.3);
		return (cosVal < 0) ? Double.NaN : Math.sqrt(cosVal);
	}

	// phi(x) = -sqrt(cos(x + 0.3)) for the negative root
	public static double phi_negative_root(double x) {
		double cosVal = Math.cos(x + 0.3);
		return (cosVal < 0) ? Double.NaN : -Math.sqrt(cosVal);
	}
}
