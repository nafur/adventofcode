#pragma once

#include "../utils/algorithm.h"
#include "../utils/parser.h"

#include <set>

template<>
struct solve<1> {
	static auto solution() {
		return std::make_pair(234, 113);
	}
	
	const std::string input = "R2, L1, R2, R1, R1, L3, R3, L5, L5, L2, L1, R4, R1, R3, L5, L5, R3, L4, L4, R5, R4, R3, L1, L2, R5, R4, L2, R1, R4, R4, L2, L1, L1, R190, R3, L4, R52, R5, R3, L5, R3, R2, R1, L5, L5, L4, R2, L3, R3, L1, L3, R5, L3, L4, R3, R77, R3, L2, R189, R4, R2, L2, R2, L1, R5, R4, R4, R2, L2, L2, L5, L1, R1, R2, L3, L4, L5, R1, L1, L2, L2, R2, L3, R3, L4, L1, L5, L4, L4, R3, R5, L2, R4, R5, R3, L2, L2, L4, L2, R2, L5, L4, R3, R1, L2, R2, R4, L1, L4, L4, L2, R2, L4, L1, L1, R4, L1, L3, L2, L2, L5, R5, R2, R5, L1, L5, R2, R4, R4, L2, R5, L5, R5, R5, L4, R2, R1, R1, R3, L3, L3, L4, L3, L2, L2, L2, R2, L1, L3, R2, R5, R5, L4, R3, L3, L4, R2, L5, R5";
	
	auto operator()() const {
		auto data = split_and_transform(input, std::string(", "),
			[](const std::string_view& sv){
				int steps = std::stoi(std::string(sv.substr(1)));
				return std::make_pair(sv.front() == 'L', steps);
			}
		);
		
		// convert "turn + steps" into "direction + steps"
		int direction = 0;
		int xdist = 0;
		int ydist = 0;
		std::set<std::pair<int,int>> visited;
		std::pair<int,int> firstTwice;
		visited.emplace(0,0);
		
		for (auto& step: data) {
			if (step.first) direction = (direction + 1) % 4;
			else direction = (direction + 3) % 4;
			std::pair<bool,int> todo;
			switch (direction) {
				case 0: todo = std::make_pair(true,step.second); break;
				case 1: todo = std::make_pair(false,-step.second); break;
				case 2: todo = std::make_pair(true,-step.second); break;
				case 3: todo = std::make_pair(false,step.second); break;
				default: break;
			}
			if (firstTwice.first == 0 && firstTwice.second == 0) {
				int step = (todo.second > 0) ? 1 : -1;
				for (int i = 0; i < std::abs(todo.second); ++i) {
					if (todo.first) xdist += step;
					else ydist += step;
					auto it = visited.emplace(xdist, ydist);
					if (!it.second) {
						firstTwice = *it.first;
					}
				}
			} else {
				if (todo.first) xdist += todo.second;
				else ydist += todo.second;
			}
		}
		
		return std::make_pair(
			std::abs(xdist) + std::abs(ydist),
			std::abs(firstTwice.first) + std::abs(firstTwice.second)
		);
	}
};
