#pragma once

#include "../utils/parser.h"
#include "../utils/algorithm.h"

#include <algorithm>
#include <ios>
#include <numeric>
#include <regex>
#include <tuple>
#include <vector>

template<>
struct solve<6> {
	static auto solution() {
		return std::make_pair("kjxfwkdh"s, "xrwcsnps"s);
	}
	const std::string input = "2016/6.input";
	
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::string res1, res2;
		for (int i = 0; i < 8; i++) {
			res1 += most_common(lines, [i](const std::string& s){ return s[i]; });
			res2 += least_common(lines, [i](const std::string& s){ return s[i]; });
		}
		return std::make_pair(res1, res2);
	}
};
