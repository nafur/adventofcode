#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <numeric>
#include <regex>
#include <tuple>
#include <vector>

template<>
struct solve<4> {
	static auto solution() {
		return std::make_pair(245102, 324);
	}
	const std::string input = "2016/4.input";
	
	using Room = std::tuple<std::string, int, std::string>;
	
	bool isValid(const Room& r) const {
		std::map<char,int> m;
		for (char c: std::get<0>(r)) m[c] += 1;
		m.erase('-');
		assert(m.size() >= 5);
		std::vector<std::pair<int,char>> checksum(m.begin(), m.end());
		std::sort(checksum.begin(), checksum.end(),
			[](const auto& l, const auto& r){
				if (l.second != r.second) return l.second > r.second;
				return l.first < r.first;
			});
		for (int i = 0; i < 5; ++i) {
			if (checksum[i].first != std::get<2>(r)[i]) return false;
		}
		return true;
	}
	
	std::string decrypt(const std::string& s, int key) const {
		std::string result;
		for (char c: s) {
			if (c != '-') {
				c = c - 'a';
				c = (c + key) % 26;
				c = c + 'a';
			}
			result += c;
		}
		return result;
	}
	
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<Room> data;
		std::regex linere("([a-z-]+)-([0-9]+)\\[([a-z]+)\\]");
		std::smatch match;
		for (const auto& line: lines) {
			if (std::regex_match(line, match, linere)) {
				data.emplace_back(match[1], std::stoi(match[2]), match[3]);
			} else {
				assert(false);
			}
		}
		int cnt = std::accumulate(data.begin(), data.end(), 0,
			[this](int i, const auto& r){ return isValid(r) ? i + std::get<1>(r) : i;
		});
		
		int secid = 0;
		for (const auto& r: data) {
			if (isValid(r)) {
				std::string name = decrypt(std::get<0>(r), std::get<1>(r));
				if (name.substr(0, 9) == "northpole") secid = std::get<1>(r);
			}
		}
		
		return std::make_pair(cnt, secid);
	}
};
