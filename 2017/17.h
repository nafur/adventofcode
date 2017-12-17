#pragma once

#include "../utils/knot_hash.h"

#include <numeric>
#include <vector>

template<>
struct solve<17> {
	static auto solution() {
		return std::make_pair(1173, 1930815);
	}
	
	static constexpr std::size_t step = 304;
	
	int first() const {
		std::vector<std::size_t> buffer = {0};
		std::size_t cur = 0;
		std::size_t insert_after = 0;
		for (std::size_t i = 1; i < 2018; ++i) {
			insert_after = (cur + step) % i;
			buffer.insert(buffer.begin() + insert_after + 1, i);
			cur = insert_after + 1;
		}
		return static_cast<int>(buffer[(insert_after + 2) % buffer.size()]);
	}
	
	int second() const {
		int cur = 0;
		int cur_after_zero = 0;
		for (int i = 1; i < 50000000; ++i) {
			cur = (cur + step) % i + 1;
			if (cur == 1) cur_after_zero = i;
		}
		return static_cast<int>(cur_after_zero);
	}
	
	auto operator()() const {
		return std::make_pair(first(), second());
	}
};
