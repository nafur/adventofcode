#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <charconv>

template<>
struct solve<1> {
	static auto solution() {
		return std::make_pair(472, 66932);
	}

	bool is_found(std::vector<bool>& found, std::size_t index) const {
		while (found.size() <= index) found.emplace_back(false);
		if (found[index]) return true;
		found[index] = true;
		return false;
		
	}

	int find_first_repeated(const std::vector<int>& v) const {
		std::vector<bool> found_p;
		std::vector<bool> found_n;
		int cur = 0;
		std::size_t id = 0;
		while (true) {
			if (cur >= 0 && is_found(found_p, cur)) return cur;
			if (cur < 0 && is_found(found_n, -cur)) return cur;
			cur += v[id];
			id = (id + 1) % v.size();
		}
	}
	
	const std::string input = "2018/1.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<int> changes;
		std::transform(lines.begin(), lines.end(), std::back_inserter(changes),
			[](const std::string& s){ return std::stoi(s); }
		);
		std::pair<int,int> admissible = {
			std::accumulate(changes.begin(), changes.end(), 0),
			find_first_repeated(changes)
		};
		return admissible;
	}
};
