#pragma once

#include "../utils/parser.h"
#include "../utils/grid.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <regex>
#include <set>

template<>
struct solve<4> {
	static auto solution() {
		return std::make_pair(98680, 9763);
	}

	struct Entry {
		int year;
		int month;
		int day;
		int hour;
		int minute;
		int event;
		bool operator<(const Entry& r) const {
			if (year != r.year) return year < r.year;
			if (month != r.month) return month < r.month;
			if (day != r.day) return day < r.day;
			if (hour != r.hour) return hour < r.hour;
			return minute < r.minute;
		}
	};

	const std::string input = "2018/4.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		const auto linere = std::regex("\\[([0-9]+)-([0-9]+)-([0-9]+) ([0-9]+):([0-9]+)\\] (.*)");
		const auto shiftre = std::regex("Guard #([0-9]+) begins shift");

		std::vector<Entry> entries;
		for (const auto& line: lines) {
			std::smatch match;
			if (std::regex_match(line, match, linere)) {
				int event = 0;
				std::smatch match2;
				std::string action = match[6];
				if (std::regex_match(action, match2, shiftre)) {
					event = std::stoi(match2[1]);
				} else if (match[6] == "falls asleep") {
					event = -1;
				} else if (match[6] == "wakes up") {
					event = -2;
				} else {
					assert(false);
				}
				entries.emplace_back(Entry {
					std::stoi(match[1]),
					std::stoi(match[2]),
					std::stoi(match[3]),
					std::stoi(match[4]),
					std::stoi(match[5]),
					event
				});
			}
		}
		std::sort(entries.begin(), entries.end());
		
		std::vector<std::pair<int,std::array<int,60>>> data;
		std::size_t last_id = 0;
		int asleep_since = 0;
		for (const auto& e: entries) {
			switch (e.event) {
				case -1:
					asleep_since = e.minute;
					break;
				case -2: {
					while (data.size() <= last_id) data.emplace_back();
					for (int i = asleep_since; i < e.minute; ++i) data[last_id].second[i] += 1;
					break;
				}
				default:
					last_id = e.event;
			}
		}

		// Strategy 1
		int res_1 = 0;
		{
			std::for_each(data.begin(), data.end(),
				[](auto& p) {
					p.first = std::accumulate(p.second.begin(), p.second.end(), 0);
				}
			);
			auto guard_it = std::max_element(data.begin(), data.end());
			int guard_id = std::distance(data.begin(), guard_it);
			auto min_it = std::max_element(guard_it->second.begin(), guard_it->second.end());
			int min_id = std::distance(guard_it->second.begin(), min_it);
			res_1 = guard_id * min_id;
		}

		// Strategy 2
		int res_2 = 0;
		{
			std::for_each(data.begin(), data.end(),
				[](auto& p) {
					p.first = *std::max_element(p.second.begin(), p.second.end());
				}
			);
			auto guard_it = std::max_element(data.begin(), data.end());
			int guard_id = std::distance(data.begin(), guard_it);
			auto min_it = std::max_element(guard_it->second.begin(), guard_it->second.end());
			int min_id = std::distance(guard_it->second.begin(), min_it);
			res_2 = guard_id * min_id;
		}


		return std::make_pair(res_1, res_2);
	}
};
