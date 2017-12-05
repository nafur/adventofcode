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
		int cnt = 0;
		for (int ip = 0; ip >= 0 && ip < program.size(); ++cnt) {
			int next = ip + program[ip];
			program[ip] = f(program[ip]);
			ip = next;
		}
		return cnt;
	}
	
	const std::string input = "2017/5.input";
	auto operator()() const {
		auto program = read_file_linewise(input, [](const auto& s){ return std::stoi(s); });
		
		return std::make_pair(
			simulate(program, [](int i){ return i+1; }),
			simulate(program, [](int i){ return (i >= 3 ? i-1 : i+1); })
		);
	}
};
