#pragma once

#include <map>
#include <numeric>
#include <utility>
#include <vector>

template<typename T>
auto sum_by_type(const std::vector<std::pair<T,int>>& data) {
	return std::accumulate(data.begin(), data.end(), std::map<T,int>(),
		[](const auto& map, const auto& pair){
			std::map<T,int> res = map;
			res[pair.first] += pair.second;
			return res;
		});
}
