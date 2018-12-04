#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <array>
#include <charconv>

template<>
struct solve<2> {
	static auto solution() {
		return std::make_pair(8820, std::string("bpacnmglhizqygfsjixtkwudr"));
	}

	std::array<int,26> get_char_map(const std::string& s) const {
		std::array<int,26> res;
		res.fill(0);
		for (auto c: s) res[c - 'a'] += 1;
		return res;
	}

	bool is_id(const std::string& s, int n) const {
		auto map = get_char_map(s);
		return std::any_of(map.begin(), map.end(),
			[n](int i){ return i == n; }
		);
	}

	int hash(const std::vector<std::string>& lines) const {
		return 
			std::count_if(lines.begin(), lines.end(),
				[this](const auto& s){ return is_id(s, 2); }
			)
			*
			std::count_if(lines.begin(), lines.end(),
				[this](const auto& s){ return is_id(s, 3); }
			)
		;
	}

	int diff_pos(const std::string& a, const std::string& b) const {
		int res = -1;
		for (std::size_t i = 0; i < std::min(a.size(), b.size()); ++i) {
			if (a[i] != b[i]) {
				if (res == -1) res = i;
				else return -1;
			}
		}
		return res;
	}

	std::string find_similar(const std::vector<std::string>& lines) const {
		for (std::size_t i = 0; i < lines.size(); ++i) {
			for (std::size_t j = i + 1; j < lines.size(); ++j) {
				int d = diff_pos(lines[i], lines[j]);
				if (d != -1) {
					return lines[i].substr(0, d) + lines[i].substr(d + 1);
				}
			}
		}
		return "";
	}

	const std::string input = "2018/2.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		
		return std::make_pair(hash(lines), find_similar(lines));
	}
};
