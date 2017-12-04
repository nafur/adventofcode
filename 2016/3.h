#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <cassert>
#include <string>

template<>
struct solve<3> {
	static auto solution() {
		return std::make_pair(869, 1544);
	}
	const std::string input = "2016/3.input";
	
	int countValid(std::vector<std::vector<int>>& data) const {
		int res = 0;
		for (auto& line: data) {
			std::sort(line.begin(), line.end());
			if (line[0] + line[1] > line[2]) ++res;
		}
		return res;
	}

	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<std::vector<int>> data;
		
		int feasible = 0;
		for (const auto& line: lines) {
			data.emplace_back(split_and_transform(line, ' ', [](const auto& s){
				return std::stoi(std::string(s));
			}));
		}
		
		std::vector<std::vector<int>> rotated;
		assert(data.size() % 3 == 0);
		for (std::size_t i = 0; i < data.size(); i+=3) {
			rotated.emplace_back(std::vector<int>({ data[i][0], data[i+1][0], data[i+2][0] }));
			rotated.emplace_back(std::vector<int>({ data[i][1], data[i+1][1], data[i+2][1] }));
			rotated.emplace_back(std::vector<int>({ data[i][2], data[i+1][2], data[i+2][2] }));
		}
		
		return std::make_pair(countValid(data), countValid(rotated));
	}
};
