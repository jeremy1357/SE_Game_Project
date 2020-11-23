#pragma once
#include <string>

struct Score {
	Score(const std::string& name, int wave, int zombieKills) {
		this->name = name;
		this->wave = wave;
		this->zombieKills = zombieKills;
	}
	bool operator <(const Score& rhs) { return this->zombieKills > rhs.zombieKills; }
	std::string name;
	int wave;
	int zombieKills;
};