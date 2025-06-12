#pragma once

#include <string>
#include <vector>

struct CandidateBorda {
	std::string nameCan;
	int scorBorda;

	CandidateBorda(std::string name, int score = 0) : nameCan(std::move(name)), scorBorda(score) {}
};

struct CandidateCondorcet {
	std::string nameCan;
	int winsCount;

	CandidateCondorcet(std::string name, int wins = 0) : nameCan(std::move(name)), winsCount(wins) {}
};

bool isNumber(const std::string &str);

bool readDataFromFile(const std::string &fileName, std::vector<std::string> &candNames,
					  std::vector<std::vector<std::string>> &votes);

std::string calculateBordaWinner(const std::vector<std::string> &candNames,
								 const std::vector<std::vector<std::string>> &votes);

std::string calculateCondorcetWinner(const std::vector<std::string> &candNames,
									 const std::vector<std::vector<std::string>> &votes);

void startVote();
