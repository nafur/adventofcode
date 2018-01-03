#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <cassert>
#include <regex>

template<>
struct solve<2> {
	static auto solution() {
		return std::make_pair(1588178, 3783758);
	}
	const std::string input = "2015/2.input";
	const std::regex linere = std::regex("([0-9]+)x([0-9]+)x([0-9]+)");
	
	int paper(int a, int b, int c) const {
		return 2*a*b + 2*b*c + 2*c*a + std::min(std::min(a*b,b*c),c*a);
	}
	int ribbon(int a, int b, int c) const {
		return std::min(std::min(a+a+b+b,b+b+c+c),c+c+a+a) + a*b*c;
	}
	
	auto operator()() const {
		int p = 0;
		int r = 0;
		for (const auto& line: read_file_linewise(input)) {
			if (std::smatch m; std::regex_match(line, m, linere)) {
				int a = std::stoi(m[1]), b = std::stoi(m[2]), c = std::stoi(m[3]);
				p += paper(a, b, c);
				r += ribbon(a, b, c);
			} else {
				assert(false);
			}
		}
		return std::make_pair(p, r);
	}
};
