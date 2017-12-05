#pragma once

#include "../utils/parser.h"

#include <algorithm>

template<>
struct solve<5> {
	static auto solution() {
		return std::make_pair(355965, 26948068);
	}
	
	template<typename F>
	int simulate(std::vector<int> program, F&& f) const {
		int ip = 0;
		int cnt = 0;
		while (ip >= 0 && ip < program.size()) {
			int next = ip + program[ip];
			program[ip] = f(program[ip]);
			ip = next;
			++cnt;
		}
		return cnt;
	}
	
	const std::string input = "2017/5.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<int> program;
		for (const auto& line: lines) {
			program.emplace_back(std::stoi(line));
		}
		
		return std::make_pair(
			simulate(program, [](int i){ return i+1; }),
			simulate(program, [](int i){ return (i >= 3 ? i-1 : i+1); })
		);
	}
};
