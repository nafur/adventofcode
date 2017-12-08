#pragma once

#include "../utils/parser.h"

#include <map>
#include <regex>
#include <string>
#include <vector>

template<>
struct solve<8> {
	static auto solution() {
		return std::make_pair(5849, 6702);
	}
	
	int doStep(std::map<std::string,int>& r, const std::smatch& step) const {
		std::string reg = step[1];
		int inc = std::stoi(step[3]) * (step[2] == "inc" ? 1 : -1);
		std::string cond = step[4];
		std::string relation = step[5];
		int compare = std::stoi(step[6]);
		if (relation == "<" && r[cond] >= compare) return 0;
		if (relation == "<=" && r[cond] > compare) return 0;
		if (relation == "==" && r[cond] != compare) return 0;
		if (relation == "!=" && r[cond] == compare) return 0;
		if (relation == ">=" && r[cond] < compare) return 0;
		if (relation == ">" && r[cond] <= compare) return 0;
		r[reg] += inc;
		return r[reg];
	}
	
	const std::string input = "2017/8.input";
	auto operator()() const {
		
		auto lines = read_file_linewise(input);
		std::map<std::string,int> registers;
		
		std::regex linere("([a-z]+) (inc|dec) ([-0-9]+) if ([a-z]+) (<|>|==|<=|>=|!=) ([-0-9]+)");
		std::smatch match;
		int maxval = 0;
		for (const auto& line: lines) {
			if (std::regex_match(line, match, linere)) {
				maxval = std::max(maxval, doStep(registers, match));
			} else {
				assert(false);
			}
		}
		auto maxelem = std::max_element(registers.begin(), registers.end(),
			[](const auto& l, const auto& r) {
				return l.second < r.second;
			});
		return std::make_pair(maxelem->second, maxval);
	}
};
