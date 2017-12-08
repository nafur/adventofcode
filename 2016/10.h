#pragma once

#include "../utils/parser.h"

#include <map>
#include <regex>
#include <string>
#include <vector>

template<>
struct solve<10> {
	static auto solution() {
		return std::make_pair(118, 143153);
	}
	
	using Target = std::pair<std::string,int>;
	
	int give(std::vector<std::pair<int,int>>& bots, std::vector<int>& outputs, int bot, const Target& low, const Target& high) const {
		int res = -1;
		if (bots[bot].first == 0 || bots[bot].second == 0) return -2;
		if (bots[bot].first > bots[bot].second) std::swap(bots[bot].first, bots[bot].second);
		if (bots[bot].first == 17 && bots[bot].second == 61) res = bot;
		if (low.first == "bot") {
			if (bots[low.second].first == 0) bots[low.second].first = bots[bot].first;
			else bots[low.second].second = bots[bot].first;
		} else {
			while (outputs.size() <= low.second) outputs.emplace_back(0);
			outputs[low.second] = bots[bot].first;
		}
		if (high.first == "bot") {
			if (bots[high.second].first == 0) bots[high.second].first = bots[bot].second;
			else bots[high.second].second = bots[bot].second;
		} else {
			while (outputs.size() <= high.second) outputs.emplace_back(0);
			outputs[high.second] = bots[bot].second;
		}
		bots[bot] = std::make_pair(0,0);
		return res;
	}
	
	void giveValue(std::vector<std::pair<int,int>>& bots, int bot, int val) const {
		while (bot >= bots.size()) {
			bots.emplace_back(0, 0);
		}
		if (bots[bot].first == 0) bots[bot].first = val;
		else bots[bot].second = val;
	}
	
	const std::string input = "2016/10.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<std::pair<int,int>> bots;
		std::vector<int> outputs;
		
		std::regex cmdre("bot ([0-9]+) gives low to (bot|output) ([0-9]+) and high to (bot|output) ([0-9]+)");
		std::regex initre("value ([0-9]+) goes to bot ([0-9]+)");
		std::smatch match;
		int maxval = 0;
		for (auto it = lines.begin(); it != lines.end(); ) {
			if (std::regex_match(*it, match, initre)) {
				giveValue(bots, std::stoi(match[2]), std::stoi(match[1]));
				it = lines.erase(it);
			}
			else ++it;
		}
		
		int res1 = 0;
		while (!lines.empty()) {
			for (auto it = lines.begin(); it != lines.end(); ) {
				if (std::regex_match(*it, match, cmdre)) {
					int res = give(bots, outputs, std::stoi(match[1]),
						std::make_pair(match[2], std::stoi(match[3])),
						std::make_pair(match[4], std::stoi(match[5]))
					);
					if (res == -2) ++it;
					else {
						it = lines.erase(it);
						if (res != -1) res1 = res;
					}
				}
				else ++it;
			}
		}
		return std::make_pair(res1, outputs[0]*outputs[1]*outputs[2]);
	}
};
