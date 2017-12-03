#pragma once

#include <numeric>
#include <string>
#include <string_view>
#include <vector>

template<typename F>
auto split_and_transform(const std::string_view& s, const std::string& c, F&& f) {
	std::vector<decltype(f(s))> res;
	std::size_t start = 0;
	while (s.substr(start,c.size()) == c) start += c.size();
	std::size_t end = s.find(c, start);
	while (end != std::string::npos) {
		res.emplace_back(f(s.substr(start, end - start)));
		start = end + c.size();
		end = s.find(c, start);
	}
	if (start < s.size()) {
		res.emplace_back(f(s.substr(start)));
	}
	return res;
}

template<typename F>
auto split_and_transform(const std::string_view& s, char c, F&& f) {
	return split_and_transform(s, std::string(1, c), std::forward<F>(f));
}

inline std::vector<std::vector<int>> parse_table(const std::string_view& input) {
	return split_and_transform(input, '\n', [](const std::string_view& line) {
		return split_and_transform(line, '\t', [](const std::string_view& number) {
			return std::stoi(std::string(number));
		});
	});
}
