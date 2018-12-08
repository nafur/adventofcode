#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <array>
#include <cassert>
#include <regex>
#include <set>

template<>
struct solve<7> {
	static auto solution() {
		return std::make_pair(std::string("IBJTUWGFKDNVEYAHOMPCQRLSZX"), 1118);
	}

	std::set<char> candidates(const std::map<char, std::set<char>>& deps) const {
		std::set<char> res;
		for (const auto& d: deps) {
			if (d.second.empty()) {
				res.insert(d.first);
			}
		}
		return res;
	}

	std::string schedule_first(std::map<char, std::set<char>> deps) const {
		std::string result;
		while (!deps.empty()) {
			std::set<char> cand = candidates(deps);
			assert(cand.size() > 0);
			char step = *cand.begin();
			deps.erase(step);
			for (auto& d: deps) {
				d.second.erase(step);
			}
			result += step;
		}
		return result;
	}

	int schedule_second(std::map<char, std::set<char>> deps) const {
		int time = 0;
		std::array<std::pair<char,int>,5> cur;
		cur.fill({'\0',0});
		while (!deps.empty()) {
			for (auto& p: cur) {
				if (p.second == 0) {
					for (auto& d: deps) {
						d.second.erase(p.first);
					}
					p = {'\0', 0};
				}
			}
			std::set<char> cand = candidates(deps);
			for (std::size_t i = 0; i < cur.size() && !cand.empty(); ++i) {
				if (cur[i].first == '\0') {
					cur[i] = {
						*cand.begin(),
						61 + int(*cand.begin() - 'A')
					};
					cand.erase(cur[i].first);
					deps.erase(cur[i].first);
				}
			}
			++time;
			for (auto& p: cur) {
				--p.second;
			}
		}
		int res = time;
		for (const auto& p: cur) {
			res = std::max(res, time + p.second);
		}
		return res;
	}

	const std::string input = "2018/7.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		const auto linere = std::regex("Step ([A-Z]) must be finished before step ([A-Z]) can begin\\.");

		std::map<char, std::set<char>> deps;
		for (const auto& line: lines) {
			std::smatch match;
			if (std::regex_match(line, match, linere)) {
				char from = std::string(match[1])[0];
				char to = std::string(match[2])[0];
				deps[to].insert(from);
				deps[from];
			}
		}

	
		return std::make_pair(schedule_first(deps), schedule_second(deps));
	}
};
