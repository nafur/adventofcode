#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <regex>
#include <set>

template<>
struct solve<6> {
	static auto solution() {
		return std::make_pair(3687, 40134);
	}

	const std::string input = "2018/6.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		const auto linere = std::regex("([0-9]+), ([0-9]+)");

		std::vector<std::tuple<int,int,int>> centers;
		int xmin = 0;
		int xmax = 0;
		int ymin = 0;
		int ymax = 0;
		for (const auto& line: lines) {
			std::smatch match;
			if (std::regex_match(line, match, linere)) {
				centers.emplace_back(
					std::stoi(match[1]),
					std::stoi(match[2]),
					0
				);
				xmin = std::min(xmin, std::get<0>(centers.back()));
				xmax = std::max(xmax, std::get<0>(centers.back()));
				ymin = std::min(ymin, std::get<1>(centers.back()));
				ymax = std::max(ymax, std::get<1>(centers.back()));
			}
		}

		std::set<std::size_t> excludes;
		int num_second = 0;
		for (int y = ymin; y <= ymax; ++y) {
			for (int x = xmin; x <= xmax; ++x) {
				std::size_t min_id = 0;
				int min = 2*(xmax - xmin);
				int mincnt = 0;
				int distsum = 0;
				for (std::size_t i = 0; i < centers.size(); ++i) {
					int dist = std::abs(x - std::get<0>(centers[i])) + std::abs(y - std::get<1>(centers[i]));
					distsum += dist;
					if (dist == min) {
						mincnt++;
					}
					if (dist < min) {
						min_id = i;
						min = dist;
						mincnt = 1;
					}
				}
				if (distsum < 10000) num_second++;
				if (mincnt > 1) {
					continue;
				}
				std::get<2>(centers[min_id]) += 1;
				if (y == ymin || y == ymax || x == xmin || x == xmax) {
					excludes.insert(min_id);
				}
			}
		}

		int max = 0;
		for (std::size_t i = 0; i < centers.size(); ++i) {
			if (excludes.find(i) != excludes.end()) continue;
			max = std::max(max, std::get<2>(centers[i]));
		}
	
		return std::make_pair(max, num_second);
	}
};
