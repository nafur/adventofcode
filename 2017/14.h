#pragma once

#include "../utils/knot_hash.h"

#include <numeric>
#include <vector>

template<>
struct solve<14> {
	static auto solution() {
		return std::make_pair(8194, 1141);
	}
	
	const std::string key = "uugsqrei";
	
	std::vector<bool> computeRow(int row) const {
		auto data = knot_hash::initial(256);
		auto input = knot_hash::from_string(key + "-" + std::to_string(row));
		auto hash = knot_hash::dense_hash(data, input, 64);
		std::vector<bool> res;
		for (int i: hash) {
			for (int b = 7; b >= 0; --b) {
				res.push_back((i & (1 << b)) != 0);
			}
		}
		return res;
	}
	
	int countBits(const std::vector<std::vector<bool>>& data) const {
		return std::accumulate(data.begin(), data.end(), 0, [](int i, const auto& d){
			return i + std::accumulate(d.begin(), d.end(), 0, [](int i, bool b){
				return i + (b ? 1 : 0);
			});	
		});
	}
	
	bool isTrue(const std::vector<std::vector<bool>>& data, int x, int y) const {
		if (y < 0 || y >= data.size()) return false;
		if (x < 0 || x >= data[y].size()) return false;
		return data[y][x];
	}
	
	bool removeRegion(std::vector<std::vector<bool>>& data) const {
		std::vector<std::pair<int,int>> queue;
		for (int y = 0; y < data.size(); ++y) {
			for (int x = 0; x < data[y].size(); ++x) {
				if (isTrue(data,x,y)) {
					queue.emplace_back(x,y);
					break;
				}
			}
			if (!queue.empty()) break;
		}
		if (queue.empty()) return false;
		
		while (!queue.empty()) {
			auto [x,y] = queue.back();
			queue.pop_back();
			if (isTrue(data, x-1, y)) queue.emplace_back(x-1, y);
			if (isTrue(data, x+1, y)) queue.emplace_back(x+1, y);
			if (isTrue(data, x, y-1)) queue.emplace_back(x, y-1);
			if (isTrue(data, x, y+1)) queue.emplace_back(x, y+1);
			data[y][x] = false;
		}
		return true;
	}
	
	auto operator()() const {
		std::vector<std::vector<bool>> grid;
		for (int i = 0; i < 128; ++i) {
			grid.emplace_back(computeRow(i));
		}
		int bitcount = countBits(grid);
		int regions = 0;
		while (removeRegion(grid)) ++regions;
		return std::make_pair(bitcount, regions);
	}
};
