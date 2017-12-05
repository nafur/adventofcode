#pragma once

#include <fstream>
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
		do {
			start = end + c.size();
			end = s.find(c, start);
		} while (start == end);
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

template<typename C>
auto split(const std::string_view& s, C&& c) {
	return split_and_transform(s, std::forward<C>(c), [](const auto& s){ return std::string(s); });
}

inline std::vector<std::vector<int>> parse_table(const std::string_view& input) {
	return split_and_transform(input, '\n', [](const std::string_view& line) {
		return split_and_transform(line, '\t', [](const std::string_view& number) {
			return std::stoi(std::string(number));
		});
	});
}

std::vector<std::string> read_file_linewise(const std::string& filename) {
	std::ifstream input(filename);
	std::vector<std::string> res;
	for (std::string line; std::getline(input, line); ) {
		res.emplace_back(std::move(line));
	}
	return res;
}

template<typename F>
auto read_file_linewise(const std::string& filename, F&& f) {
	std::ifstream input(filename);
	std::vector<decltype(f(filename))> res;
	for (std::string line; std::getline(input, line); ) {
		res.emplace_back(f(line));
	}
	return res;
}
