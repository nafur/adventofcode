#pragma once

#include "../utils/parser.h"

#include <map>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<11> {
	static auto solution() {
		return std::make_pair(743, 1493);
	}
	
	int distance(int x, int y) const {
		x = std::abs(x);
		y = std::abs(y);
		if (x >= y) return x;
		return x + (y - x) / 2;
	}
	
	std::pair<int,int> walk(const std::vector<std::string>& path) const {
		std::pair<int,int> pos = std::make_pair(0, 0);
		int max_dist = 0;
		for (const auto& step: path) {
			if (step == "n") {
				pos.second += 2;
			} else if (step == "ne") {
				pos.first += 1;
				pos.second += 1;
			} else if (step == "se") {
				pos.first += 1;
				pos.second -= 1;
			} else if (step == "s") {
				pos.second -= 2;
			} else if (step == "sw") {
				pos.first -= 1;
				pos.second -= 1;
			} else if (step == "nw") {
				pos.first -= 1;
				pos.second += 1;
			}
			int cur_dist = distance(pos.first, pos.second);
			if (cur_dist > max_dist) max_dist = cur_dist;
		}
		return std::make_pair(distance(pos.first, pos.second), max_dist);
	}
	
	const std::string input = "2017/11.input";
	auto operator()() const {
		return walk(split(read_file(input), ','));
	}
};
