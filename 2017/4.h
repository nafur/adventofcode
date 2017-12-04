#pragma once

#include "../utils/parser.h"

#include <algorithm>

template<>
struct solve<4> {
	static auto solution() {
		return std::make_pair(337, 231);
	}
	
	const std::string input = "2017/4.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::pair<int,int> admissible;
		for (const auto& line: lines) {
			auto words = split(line, ' ');
			
			std::sort(words.begin(), words.end());
			auto it1 = std::unique(words.begin(), words.end());
			if (it1 != words.end()) continue;
			++admissible.first;
			
			for (std::string& w: words) {
				std::sort(w.begin(), w.end());
			}
			std::sort(words.begin(), words.end());
			auto it2 = std::unique(words.begin(), words.end());
			if (it2 == words.end()) ++admissible.second;
		}
		return admissible;
	}
};
