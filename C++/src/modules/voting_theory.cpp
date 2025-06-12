#include "../../include/modules/voting_theory.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

bool isNumber(const std::string &str) {
	for (char const &chr : str) {
		if (std::isdigit(chr) == 0)
			return false;
	}
	return true;
}

bool readDataFromFile(const std::string &fileName, std::vector<std::string> &candNames,
					  std::vector<std::vector<std::string>> &votes) {
	std::ifstream inputFile(fileName);
	if (!inputFile.is_open()) {
		std::cerr << "Не удалось открыть файл: " << fileName << std::endl;
		return false;
	}

	std::string lineInput;

	if (std::getline(inputFile, lineInput)) {
		std::stringstream ssLine(lineInput);
		std::string candName;
		while (ssLine >> candName) {
			candNames.push_back(candName);
		}
	} else {
		std::cerr << "Файл пуст или некорректный формат (нет имен кандидатов)." << std::endl;
		return false;
	}

	if (candNames.empty()) {
		std::cerr << "Нет кандидатов в файле." << std::endl;
		return false;
	}

	int numVoters = 0;
	if (std::getline(inputFile, lineInput)) {
		if (isNumber(lineInput)) {
			numVoters = std::stoi(lineInput);
		} else {
			std::cerr << "Некорректный формат количества избирателей: " << lineInput << std::endl;
			return false;
		}
	} else {
		std::cerr << "Некорректный формат файла (нет количества избирателей)." << std::endl;
		return false;
	}

	if (numVoters <= 0) {
		std::cerr << "Количество избирателей должно быть положительным." << std::endl;
		return false;
	}

	for (int i = 0; i < numVoters; ++i) {
		if (std::getline(inputFile, lineInput)) {
			std::stringstream ssLine(lineInput);
			std::vector<std::string> voterPref;
			std::string candidate;
			while (ssLine >> candidate) {
				bool found = false;
				for (const auto &existingCand : candNames) {
					if (existingCand == candidate) {
						found = true;
						break;
					}
				}
				if (!found) {
					std::cerr << "Неизвестный кандидат '" << candidate << "' в голосе избирателя " << (i + 1)
							  << std::endl;
					return false;
				}
				voterPref.push_back(candidate);
			}
			if (voterPref.size() != candNames.size()) {
				std::cerr << "Избиратель " << (i + 1) << " не предоставил полный рейтинг кандидатов." << std::endl;
				return false;
			}
			votes.push_back(voterPref);
		} else {
			std::cerr << "Некорректное количество строк с голосами избирателей." << std::endl;
			return false;
		}
	}

	inputFile.close();
	return true;
}

std::string calculateBordaWinner(const std::vector<std::string> &candNames,
								 const std::vector<std::vector<std::string>> &votes) {
	std::map<std::string, int> candScores;
	for (const auto &name : candNames) {
		candScores[name] = 0;
	}

	int numCandidates = static_cast<int>(candNames.size());

	for (const auto &voterPref : votes) {
		for (int i = 0; i < numCandidates; ++i) {
			const std::string &currentCand = voterPref[i];
			int points = numCandidates - 1 - i;
			candScores[currentCand] += points;
		}
	}

	std::string winnerBorda = "Нет победителя";
	int maxScore = -1;

	for (const auto &pair : candScores) {
		if (pair.second > maxScore) {
			maxScore = pair.second;
			winnerBorda = pair.first;
		}
	}

	return winnerBorda;
}

std::string calculateCondorcetWinner(const std::vector<std::string> &candNames,
									 const std::vector<std::vector<std::string>> &votes) {
	int numCandidates = static_cast<int>(candNames.size());

	if (numCandidates <= 1) {
		return numCandidates == 1 ? candNames[0] : "Нет победителя (недостаточно кандидатов)";
	}

	std::vector<std::vector<int>> pairwiseWins(numCandidates, std::vector<int>(numCandidates, 0));

	for (const auto &voterPref : votes) {
		for (int i = 0; i < numCandidates; ++i) {
			for (int j = i + 1; j < numCandidates; ++j) {
				int posCandI = -1, posCandJ = -1;
				for (int k = 0; k < numCandidates; ++k) {
					if (voterPref[k] == candNames[i]) {
						posCandI = k;
					}
					if (voterPref[k] == candNames[j]) {
						posCandJ = k;
					}
				}

				if (posCandI < posCandJ) {
					pairwiseWins[i][j]++;
				} else {
					pairwiseWins[j][i]++;
				}
			}
		}
	}

	for (int i = 0; i < numCandidates; ++i) {
		bool isCondorcetWinner = true;
		for (int j = 0; j < numCandidates; ++j) {
			if (i == j)
				continue;
			if (pairwiseWins[i][j] <= pairwiseWins[j][i]) {
				isCondorcetWinner = false;
				break;
			}
		}
		if (isCondorcetWinner) {
			return candNames[i];
		}
	}

	return "Нет победителя Кондорсе (цикл)";
}

void startVote() {
	std::vector<std::string> candNames;
	std::vector<std::vector<std::string>> votes;

	if (!readDataFromFile("../voting_theory.conf", candNames, votes)) {
		std::cerr << "Ошибка при чтении данных из файла!" << std::endl;
		return;
	}

	// Вычисление победителя по методу Борда
	std::string bordaWinner = calculateBordaWinner(candNames, votes);
	std::cout << std::string(30, '-') << std::endl;
	std::cout << "Победитель по методу Борда: " << bordaWinner << std::endl;
	std::cout << std::string(30, '-') << std::endl;

	// Вычисление победителя по методу Кондорсе
	std::string condorcetWinner = calculateCondorcetWinner(candNames, votes);
	std::cout << "Победитель по методу Кондорсе: " << condorcetWinner << std::endl;
	std::cout << std::string(30, '-') << std::endl;

	if (bordaWinner != condorcetWinner) {
		std::cout << "Примечание: Методы Борда и Кондорсе дали разные результаты." << std::endl;
		std::cout << "Это может произойти из-за различий в алгоритмах подсчета." << std::endl;
	}

	std::cout << std::endl;
	std::cout << std::string(30, '=') << std::endl;
	std::cout << "Анализ методов:" << std::endl;
	std::cout << std::endl;
	std::cout << "Метод Борда:" << std::endl;
	std::cout << "Преимущества: Все голоса учитываются, каждый кандидат получает очки." << std::endl;
	std::cout << "Недостатки: Может быть подвержен 'стратегическому голосованию', когда избиратели не голосуют за "
				 "своего истинного фаворита, чтобы повлиять на результат. Также может выбрать "
				 "кандидата, который не является победителем Кондорсе."
			  << std::endl;
	std::cout << std::endl;
	std::cout << "Метод Кондорсе:" << std::endl;
	std::cout << "Преимущества: Выбирает кандидата, который может победить любого другого кандидата в парном "
				 "сравнении, что часто считается наиболее 'справедливым' выбором."
			  << std::endl;
	std::cout << "Недостатки: Победитель Кондорсе не всегда существует (так называемый 'парадокс Кондорсе' или "
				 "'цикл'). В таких случаях метод не дает однозначного результата."
			  << std::endl;
	std::cout << std::string(30, '=') << std::endl;
}
