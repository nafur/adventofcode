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
struct solve<7> {
	static auto solution() {
		return std::make_pair(118, 260);
	}
	const std::string input = "2016/7.input";
	
	std::regex abbare = std::regex("([a-z])([a-z])\\2\\1");
	std::regex abare = std::regex("([a-z])([a-z])\\1");
	
	std::vector<std::string> getAbbas(const std::string& s, const std::regex& re) const {
		std::vector<std::string> res;
		std::string_view sv(s);
		std::match_results<std::string_view::const_iterator> match;
		while (std::regex_search(sv.begin(), sv.end(), match, re)) {
			std::string m = match[0];
			sv.remove_prefix(match.position() + 1);
			if (m[0] == m[1]) continue;
			res.emplace_back(m);
		}
		return res;
	}
	
	std::vector<std::string> getAbbas(const std::vector<std::string>& v, const std::regex& re) const {
		std::vector<std::string> res;
		for (const auto& s: v) {
			auto tmp = getAbbas(s, re);
			res.insert(res.end(), tmp.begin(), tmp.end());
		}
		return res;
	}
	
	bool contains_reversed(const std::vector<std::string>& v, const std::string& aba) const {
		std::string tmp({aba[1], aba[0], aba[1]});
		return std::find(v.begin(), v.end(), tmp) != v.end();
	}
	
	auto separate(const std::string& line) const {
		std::pair<std::vector<std::string>,std::vector<std::string>> res;
		auto parts = split_by_multiple(line, [](char c){ return (c == '[') || (c == ']'); });
		bool first = true;
		for (auto& p: parts) {
			if (first) res.first.emplace_back(std::move(p));
			else res.second.emplace_back(std::move(p));
			first = !first;
		}
		return res;
	}
	
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::regex outsidere("([a-z]+)");
		std::regex insidere("\\[([a-z]+)\\]");
		int count1 = 0;
		int count2 = 0;
		for (const auto& line: lines) {
			auto res = separate(line);
			
			auto abba1 = getAbbas(res.first, abbare);
			auto abba2 = getAbbas(res.second, abbare);
			if (!abba1.empty() && abba2.empty()) {
				++count1;
			}
			
			auto aba1 = getAbbas(res.first, abare);
			auto aba2 = getAbbas(res.second, abare);
			for (const auto& aba: aba1) {
				if (contains_reversed(aba2, aba)) {
					++count2;
					break;
				}
			}
		}
		return std::make_pair(count1, count2);
	}
};
