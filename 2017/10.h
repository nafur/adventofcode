#pragma once

#include <sstream>
#include <vector>

template<>
struct solve<10> {
	static auto solution() {
		return std::make_pair(826, "d067d3f14d07e09c2e7308c3926605c4"s);
	}
	
	const std::vector<int> input = {120,93,0,90,5,80,129,74,1,165,204,255,254,2,50,113};
	const std::string key = "120,93,0,90,5,80,129,74,1,165,204,255,254,2,50,113";
	
	std::vector<int> reverse(const std::vector<int>& data, int cur, int len) const {
		std::vector<int> res(data.begin(), data.end());
		for (int i = 0; i < len; i++) {
			res[(cur + len - 1 - i) % res.size()] = data[(cur + i) % data.size()];
		}
		return res;
	}
	
	void one_round(std::vector<int>& data, const std::vector<int>& key, int& cur, int& skip) const {
		for (int i: key) {
			data = reverse(data, cur, i);
			cur = (cur + i + skip) % data.size();
			++skip;
		}
	}
	
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
		int cur = 0;
		int skip = 0;
		one_round(data, input, cur, skip);
		return data[0] * data[1];
	}
	
	std::string hash2(std::vector<int> data) const {
		std::vector<int> input;
		for (char c: key) input.emplace_back(c);
		input.insert(input.end(), {17, 31, 73, 47, 23});
		
		int cur = 0;
		int skip = 0;
		for (int i = 0; i < 64; ++i) {
			one_round(data, input, cur, skip);
		}
		return make_dense(data);
	}
	
	
	auto operator()() const {
		std::vector<int> data;
		for (int i = 0; i < 256; ++i) data.emplace_back(i);
		
		return std::make_pair(hash1(data), hash2(data));
	}
};
