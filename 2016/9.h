#pragma once

#include "../utils/parser.h"
#include "../utils/algorithm.h"

#include <algorithm>
#include <ios>
#include <numeric>
#include <regex>
#include <sstream>
#include <tuple>
#include <vector>

template<>
struct solve<9> {
	static auto solution() {
		return std::make_pair(115118ul, 11107527530ul);
	}
	const std::string input = "2016/9.input";
	
	std::regex marker = std::regex("^([^(]*)\\(([0-9]+)x([0-9]+)\\)");
	
	std::string decompress_1(std::string_view sv) const {
		std::match_results<std::string_view::const_iterator> match;
		std::stringstream out;
		
		while (std::regex_search(sv.begin(), sv.end(), match, marker)) {
			assert(match.position() == 0);
			out << match[1];
			int len = std::stoi(match[2]);
			int cnt = std::stoi(match[3]);
			sv.remove_prefix(match.length());
			for (int i = 0; i < cnt; ++i) {
				out << std::string(sv.substr(0, len));
			}
			sv.remove_prefix(len);
		}
		return out.str();
	}
	
	std::size_t decompress_2_length(std::string_view sv) const {
		std::match_results<std::string_view::const_iterator> match;
		long long res = 0;
		
		while (std::regex_search(sv.begin(), sv.end(), match, marker)) {
			assert(match.position() == 0);
			res += match.length(1);
			std::size_t len = std::stoull(match[2]);
			std::size_t cnt = std::stoull(match[3]);
			sv.remove_prefix(match.length());
			res += decompress_2_length(sv.substr(0, len)) * cnt;
			sv.remove_prefix(len);
		}
		return res + sv.length();
	}
	
	auto operator()() const {
		std::string data = read_file(input);
		return std::make_pair(decompress_1(data).length(), decompress_2_length(data));
	}
};
