#pragma once

#include "../utils/parser.h"

#include <bitset>
#include <cstdint>
#include <unordered_map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<24> {
	static auto solution() {
		return std::make_pair(1906, 1824);
	}
	
	const std::string input = "2017/24.input";
	using Data = std::vector<std::pair<int,int>>;
	
	std::pair<int,std::pair<int,int>> explore(int depth, int tail, const Data& d) const {
		int max = tail;
		std::pair<int,int> longest = std::make_pair(0,tail);
		std::vector<std::size_t> targets;
		for (std::size_t i = 0; i < d.size(); ++i) {
			if (d[i].first == tail || d[i].second == tail) targets.emplace_back(i);
		}
		for (auto i: targets) {
			int to = (d[i].first == tail ? d[i].second : d[i].first);
			Data tmp(d);
			std::swap(tmp[i], tmp.back());
			tmp.pop_back();
			auto cur = explore(depth + 1, to, tmp);
			max = std::max(max, cur.first + tail + tail);
			auto [len,weight] = cur.second;
			if (len+1 > longest.first) {
				longest = std::make_pair(len+1, weight + tail + tail);
			} else if (len+1 == longest.first) {
				longest.second = std::max(longest.second, weight + tail + tail);
			}
		}
		return std::make_pair(max, longest);
	}
	
	auto operator()() const {
		Data d;
		for (const auto& line: read_file_linewise(input)) {
			auto l = split(line, '/');
			d.emplace_back(std::stoi(l[0]), std::stoi(l[1]));
		}
		
		auto res = explore(0, 0, d);
		return std::make_pair(res.first, res.second.second);
	}
};
