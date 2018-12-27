#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <regex>
#include <set>

template<>
struct solve<10> {
	static auto solution() {
		return std::make_pair("AJZNXHKE"s, 10905);
	}

	std::vector<std::pair<int,int>> get_current(const std::vector<std::tuple<int,int,int,int>>& objects, int t) const {
		std::vector<std::pair<int,int>> cur;
		for (const auto& o: objects) {
			cur.emplace_back(
				std::get<0>(o) + t * std::get<2>(o),
				std::get<1>(o) + t * std::get<3>(o)
			);
		}
		return cur;
	}

	long long compactness(const std::vector<std::tuple<int,int,int,int>>& objects, int t) const {
		std::vector<std::pair<int,int>> cur = get_current(objects, t);
		long long x = 0;
		long long y = 0;
		for (const auto& c: cur) {
			x += c.first;
			y += c.second;
		}
		x = x / objects.size();
		y = y / objects.size();
		long long diff = 0;
		for (const auto& c: cur) {
			diff += (c.first - x) * (c.first - x) + (c.second - y) * (c.second - y);
		}
		return diff;
	}

	void print(const std::vector<std::pair<int,int>>& points) const {
		auto xr = std::make_pair(points.front().first, points.front().first);
		auto yr = std::make_pair(points.front().second, points.front().second);
		for (const auto& p: points) {
			xr.first = std::min(xr.first, p.first);
			xr.second = std::max(xr.second, p.first);
			yr.first = std::min(yr.first, p.second);
			yr.second = std::max(yr.second, p.second);
		}

		for (int y = yr.first; y <= yr.second; ++y) {
			for (int x = xr.first; x <= xr.second; ++x) {
				if (std::find(points.begin(), points.end(), std::make_pair(x, y)) != points.end()) {
					std::cout << "#";
				} else {
					std::cout << " ";
				}
			}
			std::cout << std::endl;
		}
	}

	const std::string input = "2018/10.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		const auto linere = std::regex("position=< *(-?[0-9]+), *(-?[0-9]+)> velocity=< *(-?[0-9]+), *(-?[0-9]+)>");

		std::vector<std::tuple<int,int,int,int>> objects;
		for (const auto& line: lines) {
			std::smatch match;
			if (std::regex_match(line, match, linere)) {
				objects.emplace_back(
					std::stoi(match[1]),
					std::stoi(match[2]),
					std::stoi(match[3]),
					std::stoi(match[4])
				);
				//std::cout << objects.back() << std::endl;
			}
		}

		auto last = compactness(objects, 0);
		int t = 0;
		for (; ; ++t) {
			auto next = compactness(objects, t+1);
			if (next > last) {
				print(get_current(objects, t));
				break;
			}
			last = next;
		}
	
		return std::make_pair("AJZNXHKE"s, t);
	}
};
