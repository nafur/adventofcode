#pragma once

#include "../utils/parser.h"

#include <cstdint>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<19> {
	static auto solution() {
		return std::make_pair("BPDKCZWHGT"s, 17728);
	}
	
	const std::string input = "2017/19.input";
	
	char curchar(const std::pair<int,int>& pos, const std::vector<std::string>& data) const {
		return data[pos.second][pos.first];
	}
	std::pair<int,int> step(const std::pair<int,int>& pos, const std::pair<int,int>& dir) const {
		return std::make_pair(pos.first + dir.first, pos.second + dir.second);
	}
	std::pair<int,int> above(const std::pair<int,int>& pos) const {
		return std::make_pair(pos.first, pos.second - 1);
	}
	std::pair<int,int> below(const std::pair<int,int>& pos) const {
		return std::make_pair(pos.first, pos.second + 1);
	}
	std::pair<int,int> left(const std::pair<int,int>& pos) const {
		return std::make_pair(pos.first - 1, pos.second);
	}
	std::pair<int,int> right(const std::pair<int,int>& pos) const {
		return std::make_pair(pos.first + 1, pos.second);
	}
	
	auto operator()() const {
		auto data = read_file_linewise(input);
		
		std::string letters;
		std::pair<int,int> pos(data[0].find('|'), 0);
		std::pair<int,int> dir(0,1);
		int steps = 0;
		
		while (dir != std::make_pair(0,0)) {
			pos = step(dir, pos);
			++steps;
			char c = curchar(pos, data);
			switch (c) {
				case '|': break;
				case '-': break;
				case '+': {
					if (dir == std::make_pair(0,1) || dir == std::make_pair(0,-1)) {
						if (curchar(left(pos), data) != ' ') {
							dir = std::make_pair(-1,0);
						} else if (curchar(right(pos), data) != ' ') {
							dir = std::make_pair(1,0);
						} else assert(false);
					} else if (dir == std::make_pair(1,0) || dir == std::make_pair(-1,0)) {
						if (curchar(above(pos), data) != ' ') {
							dir = std::make_pair(0,-1);
						} else if (curchar(below(pos), data) != ' ') {
							dir = std::make_pair(0,1);
						} else assert(false);
					} else assert(false);
					break;
				}
				case ' ': 
					dir = std::make_pair(0,0);
					break;
				default: {
					assert(c >= 'A' && c <= 'Z');
					letters += c;
				}
			}
		}
				
		return std::make_pair(letters, steps);
	}
};
