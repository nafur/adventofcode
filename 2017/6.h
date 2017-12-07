#pragma once

#include <algorithm>
#include <iostream>
#include <vector>

template<>
struct solve<6> {
	static auto solution() {
		return std::make_pair(4074, 2793);
	}
	
	std::vector<int> redistribute(const std::vector<int>& memory) const {
		auto res = memory;
		auto it = std::max_element(res.begin(), res.end());
		int cnt = *it;
		*it = 0;
		while (cnt > 0) {
			++it;
			if (it == res.end()) it = res.begin();
			*it += 1;
			cnt -= 1;
		}
		return res;
	}
	
	const std::vector<int> input = std::vector<int>({11, 11, 13, 7, 0, 15, 5, 5, 4, 4, 1, 1, 7, 1, 15, 11});
	auto operator()() const {
		std::vector<std::vector<int>> history;
		auto memory = input;
		
		int cnt = 0;
		auto it = history.end();
		while (it == history.end()) {
			history.emplace_back(memory);
			memory = redistribute(memory);
			it = std::find(history.begin(), history.end(), memory);
			++cnt;
		}
		int cycle_length = history.size() - std::distance(history.begin(), it);
		return std::make_pair(cnt, cycle_length);
	}
};
