#pragma once

#include "../utils/parser.h"

#include <map>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<9> {
	static auto solution() {
		return std::make_pair(16869, 7284);
	}
	
	std::pair<int,std::size_t> skip_garbage(std::string_view& sv) const {
		assert(sv[0] == '<');
		int garbage = 0;
		std::size_t curlen = sv.size();
		sv.remove_prefix(1);
		while (sv[0] != '>') {
			//std::cout << "Scanning:" << sv << std::endl;
			if (sv[0] == '!') sv.remove_prefix(2);
			else {
				sv.remove_prefix(1);
				++garbage;
			}
		}
		assert(sv[0] == '>');
		sv.remove_prefix(1);
		return std::make_pair(garbage, curlen - sv.size());
	}
	
	std::tuple<int,int,std::size_t> score_group(std::string_view sv, int nesting = 1) const {
		assert(sv[0] == '{');
		int score = nesting;
		int garbage = 0;
		std::size_t len = 1;
		sv.remove_prefix(1);
		
		while (true) {
			if (sv[0] == '{') {
				auto inner = score_group(sv, nesting + 1);
				score += std::get<0>(inner);
				garbage += std::get<1>(inner);
				len += std::get<2>(inner);
				sv.remove_prefix(std::get<2>(inner));
			}
			else if (sv[0] == ',') {
				len += 1;
				sv.remove_prefix(1);
			}
			else if (sv[0] == '<') {
				auto g = skip_garbage(sv);
				garbage += g.first;
				len += g.second;
			}
			else if (sv[0] == '}') {
				break;
			}
		}
		
		assert(sv[0] == '}');
		++len;
		sv.remove_prefix(1);
		
		return std::make_tuple(score, garbage, len);
	}
	
	const std::string input = "2017/9.input";
	auto operator()() const {
		auto data = read_file(input);
		while (data.back() == '\n') data.pop_back();
		
		assert(data[0] == '{');
		auto res = score_group(data);
		assert(std::get<2>(res) == data.size());
		return std::make_pair(std::get<0>(res), std::get<1>(res));
	}
};
