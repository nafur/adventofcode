#pragma once

#include "../utils/parser.h"
#include "../utils/algorithm.h"

#include <algorithm>
#include <ios>
#include <numeric>
#include <regex>
#include <tuple>
#include <vector>

template<>
struct solve<8> {
	static auto solution() {
		return 123;
	}
	const std::string input = "2016/8.input";
	
	std::regex rectre = std::regex("rect ([0-9]+)x([0-9]+)");
	std::regex rotrow = std::regex("rotate row y=([0-9]+) by ([0-9]+)");
	std::regex rotcol = std::regex("rotate column x=([0-9]+) by ([0-9]+)");
	
	void rect(std::vector<std::vector<bool>>& screen, int A, int B) const {
		for (int x = 0; x < A; ++x) {
			for (int y = 0; y < B; ++y) {
				screen[y][x] = true;
			}
		}
	}
	void rotate_row(std::vector<std::vector<bool>>& screen, int A, int B) const {
		std::vector<bool> tmp(screen[A].size());
		for (std::size_t i = 0; i < tmp.size(); ++i) {
			tmp[(i + B) % tmp.size()] = screen[A][i];
		}
		screen[A] = tmp;
	}
	void rotate_column(std::vector<std::vector<bool>>& screen, int A, int B) const {
		std::vector<bool> tmp(screen.size());
		for (std::size_t i = 0; i < tmp.size(); ++i) {
			tmp[(i + B) % tmp.size()] = screen[i][A];
		}
		for (std::size_t i = 0; i < tmp.size(); ++i) {
			screen[i][A] = tmp[i];
		}
	}
	
	auto operator()() const {
		auto lines = read_file_linewise(input);
		
		std::vector<std::vector<bool>> data(6, std::vector<bool>(50, false));
		std::smatch m;
		for (const auto& line: lines) {
			if (std::regex_match(line, m, rectre)) {
				rect(data, std::stoi(m[1]), std::stoi(m[2]));
			} else if (std::regex_match(line, m, rotrow)) {
				rotate_row(data, std::stoi(m[1]), std::stoi(m[2]));
			} else if (std::regex_match(line, m, rotcol)) {
				rotate_column(data, std::stoi(m[1]), std::stoi(m[2]));
			}
		}
		int cnt = std::accumulate(data.begin(), data.end(), 0, [](int s, const auto& v) {
			return s + std::count(v.begin(), v.end(), true);
		});
		
		for (const auto& d: data) {
			for (bool b: d) {
				std::cout << (b ? "#" : " ");
			}
			std::cout << std::endl;
		}
		
		return cnt;
	}
};
