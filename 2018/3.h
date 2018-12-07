#pragma once

#include "../utils/parser.h"
#include "../utils/grid.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <regex>
#include <set>

template<>
struct solve<3> {
	static auto solution() {
		return std::make_pair(106501, 632);
	}

	struct Entry {
		int id;
		int x;
		int y;
		int w;
		int h;
	};

	const std::string input = "2018/3.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		const auto linere = std::regex("#([0-9]+) @ ([0-9]+),([0-9]+): ([0-9]+)x([0-9]+)");

		Grid<std::pair<int,int>> grid;
		std::set<int> candidates;
		std::vector<Entry> entries;
		for (const auto& line: lines) {
			std::smatch match;
			if (std::regex_match(line, match, linere)) {
				entries.emplace_back(Entry {
					std::stoi(match[1]),
					std::stoi(match[2]),
					std::stoi(match[3]),
					std::stoi(match[4]),
					std::stoi(match[5])
				});
				const auto& e = entries.back();
				candidates.emplace(e.id);
				for (int x = e.x; x < e.x + e.w; ++x) {
					for (int y = e.y; y < e.y + e.h; ++y) {
						if (grid(x, y).first == 0) {
							grid(x, y).second = entries.back().id;
						} else {
							candidates.erase(grid(x, y).second);
							candidates.erase(e.id);
						}
						grid(x, y).first += 1;
					}
				}

			}
		}
		int count = 0;
		for (const auto& g: grid.mData) {
			for (const auto& c: g) {
				if (c.first > 1) ++count;
			}
		}
		assert(candidates.size() == 1);
		
		return std::make_pair(count, *candidates.begin());
	}
};
