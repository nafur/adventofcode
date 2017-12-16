#pragma once

#include "../utils/knot_hash.h"

#include <numeric>
#include <vector>

template<>
struct solve<15> {
	static auto solution() {
		return std::make_pair(569, 298);
	}
	
	static constexpr unsigned long initial_a = 116;
	static constexpr unsigned long initial_b = 299;
	
	int agree_1(unsigned long a, unsigned long b) const {
		int res = 0;
		for (unsigned long i = 0; i < 40000000; ++i) {
			a = (a * 16807) % 2147483647;
			b = (b * 48271) % 2147483647;
			if ((a & 0b1111111111111111) == (b & 0b1111111111111111)) ++res;
		}
		return res;
	}
	int agree_2(unsigned long a, unsigned long b) const {
		int res = 0;
		for (unsigned long i = 0; i < 5000000; ++i) {
			do {
				a = (a * 16807) % 2147483647;
			} while ((a & 0b11) != 0);
			do {
				b = (b * 48271) % 2147483647;
			} while ((b & 0b111) != 0);
			if ((a & 0b1111111111111111) == (b & 0b1111111111111111)) ++res;
		}
		return res;
	}
	
	auto operator()() const {
		return std::make_pair(agree_1(initial_a, initial_b), agree_2(initial_a, initial_b));
	}
};
