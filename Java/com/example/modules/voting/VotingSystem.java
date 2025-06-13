package com.example.modules.voting;

import com.example.modules.voting.models.VoteReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public final class VotingSystem {

	private VotingSystem() {}

	/**
	 * Вычисляет победителя по методу Борда.
	 * Соответствует calculateBordaWinner.
	 */
	private static String calculateBordaWinner(
		List<String> candNames,
		List<List<String>> votes
	) {
		Map<String, Integer> candScores = new HashMap<>();
		for (String name : candNames) {
			candScores.put(name, 0); //
		}

		int numCandidates = candNames.size();
		for (List<String> voterPref : votes) { //
			for (int i = 0; i < numCandidates; i++) {
				String currentCand = voterPref.get(i);
				int points = numCandidates - 1 - i; //
				candScores.merge(currentCand, points, Integer::sum);
			}
		}

		String winnerBorda = "Нет победителя";
		int maxScore = -1;
		for (Map.Entry<String, Integer> entry : candScores.entrySet()) {
			if (entry.getValue() > maxScore) { //
				maxScore = entry.getValue();
				winnerBorda = entry.getKey();
			}
		}
		return winnerBorda; //
	}

	/**
	 * Вычисляет победителя по методу Кондорсе.
	 * Соответствует calculateCondorcetWinner.
	 */
	private static String calculateCondorcetWinner(
		List<String> candNames,
		List<List<String>> votes
	) {
		int numCandidates = candNames.size();
		if (numCandidates <= 1) {
			return numCandidates == 1
				? candNames.getFirst()
				: "Нет победителя (недостаточно кандидатов)"; //
		}

		int[][] pairwiseWins = new int[numCandidates][numCandidates]; //

		for (List<String> voterPref : votes) {
			for (int i = 0; i < numCandidates; i++) {
				for (int j = i + 1; j < numCandidates; j++) {
					String candI = candNames.get(i);
					String candJ = candNames.get(j);
					int posCandI = voterPref.indexOf(candI); //
					int posCandJ = voterPref.indexOf(candJ);

					if (posCandI < posCandJ) {
						pairwiseWins[i][j]++;
					} else {
						pairwiseWins[j][i]++; //
					}
				}
			}
		}

		for (int i = 0; i < numCandidates; i++) {
			boolean isCondorcetWinner = true; //
			for (int j = 0; j < numCandidates; j++) {
				if (i == j) continue;
				if (pairwiseWins[i][j] <= pairwiseWins[j][i]) { //
					isCondorcetWinner = false;
					break;
				}
			}
			if (isCondorcetWinner) {
				return candNames.get(i);
			}
		}

		return "Нет победителя Кондорсе (цикл)";
	}

	/**
	 * Основной метод модуля, запускающий логику голосования.
	 * Соответствует startVote.
	 */
	public static void run() {
		try {
			// Путь к файлу. В C++ он был ../voting_theory.conf.
			// Здесь предполагается, что он находится в корне проекта.
			VoteReader.VotingData data = VoteReader.readFromFile(
				"voting_theory.conf"
			); //

			String bordaWinner = calculateBordaWinner(
				data.candidateNames(),
				data.votes()
			); //
			String condorcetWinner = calculateCondorcetWinner(
				data.candidateNames(),
				data.votes()
			); //

			System.out.println("-".repeat(30));
			System.out.println("Победитель по методу Борда: " + bordaWinner); //
			System.out.println("-".repeat(30));
			System.out.println(
				"Победитель по методу Кондорсе: " + condorcetWinner
			); //
			System.out.println("-".repeat(30));

			if (!bordaWinner.equals(condorcetWinner)) { //
				System.out.println(
					"Примечание: Методы Борда и Кондорсе дали разные результаты."
				); //
				System.out.println(
					"Это может произойти из-за различий в алгоритмах подсчета."
				); //
			}

			// Вывод анализа методов
			System.out.println("\n" + "=".repeat(30)); //
			System.out.println("Анализ методов:");
			System.out.println("\nМетод Борда:"); //
			System.out.println(
				"Преимущества: Все голоса учитываются, каждый кандидат получает очки."
			); //
			System.out.println(
				"Недостатки: Может быть подвержен 'стратегическому голосованию'."
			); //
			System.out.println("\nМетод Кондорсе:"); //
			System.out.println(
				"Преимущества: Выбирает кандидата, который может победить любого другого в парном сравнении."
			); //
			System.out.println(
				"Недостатки: Победитель Кондорсе не всегда существует (парадокс Кондорсе)."
			); //
			System.out.println("=".repeat(30));
		} catch (IOException e) {
			System.err.println(
				"Ошибка при обработке данных голосования: " + e.getMessage()
			); //
		}
	}
}
