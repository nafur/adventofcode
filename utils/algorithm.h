#pragma once

#include <algorithm>
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

template<typename T, typename F, typename Comp>
auto choose_by_frequency(const std::vector<T>& items, F&& f, Comp&& c) {
	using return_type = decltype(f(items.front()));
	std::map<return_type,int> cnt;
	for (const auto& t: items) ++cnt[f(t)];
	std::vector<std::pair<return_type,int>> occurrences(cnt.begin(), cnt.end());
	std::sort(occurrences.begin(), occurrences.end(), c);
	return occurrences.front().first;
}

template<typename T, typename F>
auto most_common(const std::vector<T>& items, F&& f) {
	return choose_by_frequency(items, std::forward<F>(f), [](const auto& l, const auto& r){
		return l.second > r.second;
	});
}

template<typename T, typename F>
auto least_common(const std::vector<T>& items, F&& f) {
	return choose_by_frequency(items, std::forward<F>(f), [](const auto& l, const auto& r){
		return l.second < r.second;
	});
}
