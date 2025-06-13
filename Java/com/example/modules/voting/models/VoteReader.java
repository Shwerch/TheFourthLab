package com.example.modules.voting.models;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;

public final class VoteReader {

	// Класс-контейнер для возврата данных из файла.
	public record VotingData(
		List<String> candidateNames,
		List<List<String>> votes
	) {}

	private VoteReader() {}

	/**
	 * Читает данные о голосовании из файла.
	 * Соответствует readDataFromFile.
	 */
	public static VotingData readFromFile(String fileName) throws IOException {
		Path path = Path.of(fileName);
		if (!Files.exists(path)) {
			throw new IOException("Не удалось открыть файл: " + fileName); //
		}

		List<String> lines = Files.readAllLines(path);
		if (lines.size() < 2) {
			throw new IOException("Файл пуст или некорректный формат."); //
		}

		// 1. Чтение имен кандидатов
		List<String> candidateNames = new ArrayList<>(
			Arrays.asList(lines.get(0).split("\\s+"))
		);
		if (candidateNames.isEmpty() || candidateNames.getFirst().isBlank()) {
			throw new IOException("Нет кандидатов в файле."); //
		}

		// 2. Чтение количества избирателей
		int numVoters;
		try {
			numVoters = Integer.parseInt(lines.get(1)); //
			if (numVoters <= 0) throw new IOException(
				"Количество избирателей должно быть положительным."
			); //
		} catch (NumberFormatException e) {
			throw new IOException(
				"Некорректный формат количества избирателей: " + lines.get(1)
			); //
		}

		if (lines.size() < 2 + numVoters) {
			throw new IOException(
				"Некорректное количество строк с голосами избирателей."
			);
		}

		// 3. Чтение голосов
		List<List<String>> votes = new ArrayList<>();
		for (int i = 0; i < numVoters; i++) {
			List<String> voterPref = new ArrayList<>(
				Arrays.asList(lines.get(i + 2).split("\\s+"))
			); //

			// Валидация
			if (voterPref.size() != candidateNames.size()) {
				throw new IOException(
					"Избиратель " +
					(i + 1) +
					" не предоставил полный рейтинг кандидатов."
				); //
			}
			for (String candidate : voterPref) {
				if (!candidateNames.contains(candidate)) {
					throw new IOException(
						"Неизвестный кандидат '" +
						candidate +
						"' в голосе избирателя " +
						(i + 1)
					); //
				}
			}
			votes.add(voterPref);
		}

		return new VotingData(candidateNames, votes); //
	}
}
