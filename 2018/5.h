#pragma once

#include "../utils/parser.h"
#include "../utils/grid.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <regex>
#include <set>

template<>
struct solve<5> {
	static auto solution() {
		return std::make_pair(106501, 632);
	}

	std::string reduce(const std::string& s) const {
		std::vector<char> result;
		for (std::size_t i = 0; i < s.size(); ++i) {
			if (result.empty()) {
				result.emplace_back(s[i]);
				continue;
			}
			if (std::abs(int(result.back()) - int(s[i])) == ('a' - 'A')) {
				result.pop_back();
			} else {
				result.emplace_back(s[i]);
			}
		}
		return std::string(result.begin(), result.end());
	}

	const std::string input = "2018/5.input";
	auto operator()() const {
		auto data = read_file(input);
		
		std::string reduced = reduce(data);
		int min_len = reduced.size();
		for (char c = 'a'; c <= 'z'; ++c) {
			std::vector<char> tmp;
			for (char d: reduced) {
				if (d == c) continue;
				if (d == (c - ('a' - 'A'))) continue;
				tmp.emplace_back(d);
			}
			int r_len = reduce(std::string(tmp.begin(), tmp.end())).size();
			min_len = std::min(min_len, r_len);
		}
		
		return std::make_pair(int(reduced.size()), min_len);
	}
};
