#pragma once

#include <vector>

namespace knot_hash {

using raw_data = std::vector<int>;

inline raw_data from_string(const std::string& s) {
	raw_data res;
	for (char c: s) res.emplace_back(c);
	res.insert(res.end(), {17, 31, 73, 47, 23});
	return res;
}

inline raw_data initial(std::size_t size) {
	raw_data data;
	for (int i = 0; i < size; ++i) data.emplace_back(i);
	return data;
}

inline raw_data reverse(const raw_data& data, int cur, int len) {
	raw_data res(data.begin(), data.end());
	for (int i = 0; i < len; i++) {
		res[(cur + len - 1 - i) % res.size()] = data[(cur + i) % data.size()];
	}
	return res;
}

inline void one_round(raw_data& data, const raw_data& key, int& cur, int& skip) {
	for (int i: key) {
		data = reverse(data, cur, i);
		cur = (cur + i + skip) % data.size();
		++skip;
	}
}

inline raw_data once(raw_data data, const raw_data& key) {
	int cur = 0;
	int skip = 0;
	one_round(data, key, cur, skip);
	return data;
}

inline raw_data hash(raw_data data, const raw_data& key, std::size_t rounds) {
	int cur = 0;
	int skip = 0;
	for (int i = 0; i < rounds; ++i) {
		one_round(data, key, cur, skip);
	}
	return data;
}

inline raw_data dense_hash(raw_data data, const raw_data& key, std::size_t rounds) {
	assert(data.size() == 256);
	data = hash(data, key, rounds);
	raw_data res;
	for (int i = 0; i < 16; ++i) {
		int x = 0;
		for (int j = 0; j < 16; ++j) {
			x = x ^ data[i*16 + j];
		}
		res.push_back(x);
	}
	return res;
}

inline std::string digest(const raw_data& data) {
	std::stringstream res;
	for (int i = 0; i < data.size(); ++i) {
		res << std::hex << (data[i] / 16) << (data[i] % 16);
	}
	return res.str();
}

}
