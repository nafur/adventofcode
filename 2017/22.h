#pragma once

#include "../utils/parser.h"
#include "../utils/grid.h"

#include <bitset>
#include <cstdint>
#include <unordered_map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<22> {
	static auto solution() {
		return std::make_pair(5305, 2511424);
	}
	
	const std::string input = "2017/22.input";
	
	using InfiniteField = InfiniteGrid<int>;
	
	void turn(std::pair<int,int>& dir, bool left) const {
		if (left) {
			dir = std::make_pair(dir.second, -dir.first);
		} else {
			dir = std::make_pair(-dir.second, dir.first);
		}
	}
	
	bool doStep1(InfiniteField& infected, std::pair<int,int>& pos, std::pair<int,int>& dir) const {
		bool res = false;
		int& inf = infected(pos);
		if (inf == 0) {
			turn(dir, true);
			inf = 2;
			res = true;
		} else {
			turn(dir, false);
			inf = 0;
		}
		pos.first += dir.first;
		pos.second += dir.second;
		return res;
	}
	
	int task1(InfiniteField infected, std::pair<int,int> pos) const {
		int infections = 0;
		auto dir = std::make_pair(0, -1);
		for (int i = 0; i < 10000; ++i) {
			if (doStep1(infected, pos, dir)) ++infections;
		}
		return infections;
	}
	
	bool doStep2(InfiniteField& infected, std::pair<int,int>& pos, std::pair<int,int>& dir) const {
		int& inf = infected(pos);
		
		switch (inf) {
			case 0: turn(dir, true); break;
			case 1: break;
			case 2: turn(dir, false); break;
			case 3: dir = std::make_pair(-dir.first, -dir.second); break;
		}
		inf = (inf + 1) % 4;
		
		pos.first += dir.first;
		pos.second += dir.second;
		return inf == 2;
	}
	
	int task2(InfiniteField infected, std::pair<int,int> pos) const {
		int infections = 0;
		auto dir = std::make_pair(0, -1);
		for (int i = 0; i < 10000000; ++i) {
			if (doStep2(infected, pos, dir)) ++infections;
		}
		return infections;
	}
	
	auto operator()() const {
		InfiniteField field;
		int y = 0;
		for (const auto& line: read_file_linewise(input)) {
			for (int x = 0; x < line.size(); ++x) {
				field(x,y) = (line[x] == '#' ? 2 : 0);
			}
			++y;
		}
		auto pos = std::make_pair(y/2,y/2);
		return std::make_pair(task1(field, pos), task2(field, pos));
	}
};
