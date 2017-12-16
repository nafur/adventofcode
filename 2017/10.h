#pragma once

#include <sstream>
#include <vector>

#include "../utils/knot_hash.h"

template<>
struct solve<10> {
	static auto solution() {
		return std::make_pair(826, "d067d3f14d07e09c2e7308c3926605c4"s);
	}
	
	const std::vector<int> input = {120,93,0,90,5,80,129,74,1,165,204,255,254,2,50,113};
	const std::string key = "120,93,0,90,5,80,129,74,1,165,204,255,254,2,50,113";
	
	std::string make_dense(const std::vector<int>& data) const {
		assert(data.size() == 256);
		std::stringstream res;
		for (int i = 0; i < 16; ++i) {
			int x = 0;
			for (int j = 0; j < 16; ++j) {
				x = x ^ data[i*16 + j];
			}
			res << std::hex << (x / 16) << (x % 16);
		}
		return res.str();
	}
	
	int hash1(std::vector<int> data) const {
		data = knot_hash::once(data, input);
		return data[0] * data[1];
	}
	
	std::string hash2(std::vector<int> data) const {
		auto input = knot_hash::from_string(key);
		return knot_hash::digest(knot_hash::dense_hash(data, input, 64));
	}
	
	
	auto operator()() const {
		std::vector<int> data = knot_hash::initial(256);
		
		return std::make_pair(hash1(data), hash2(data));
	}
};
