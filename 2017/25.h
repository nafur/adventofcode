#pragma once

#include "../utils/parser.h"

#include <bitset>
#include <cstdint>
#include <unordered_map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<25> {
	static auto solution() {
		return 4225;
	}
	
	using TM = std::tuple<std::vector<bool>, int, char>;
	
	int& position(TM& tm) const { return std::get<int>(tm); }
	char& state(TM& tm) const { return std::get<char>(tm); }
	auto& tape(TM& tm) const { return std::get<std::vector<bool>>(tm); }
	auto tape_cell(TM& tm) const {
		auto pos = position(tm);
		std::size_t id = (pos >= 0 ? pos*2 : (-pos)*2-1);
		if (id >= tape(tm).size()) tape(tm).resize(id+1);
		return tape(tm)[id];
	}
	int checksum(TM& tm) const {
		int res = 0;
		for (const auto& bit: tape(tm)) {
			if (bit) ++res;
		}
		return res;
	}
	
	void step(TM& tm) const {
		switch (state(tm)) {
			case 'A':
				if (!tape_cell(tm)) {
					tape_cell(tm) = true;
					position(tm) += 1;
					state(tm) = 'B';
				} else {
					tape_cell(tm) = true;
					position(tm) -= 1;
					state(tm) = 'E';
				}
				break;
			case 'B':
				if (!tape_cell(tm)) {
					tape_cell(tm) = true;
					position(tm) += 1;
					state(tm) = 'C';
				} else {
					tape_cell(tm) = true;
					position(tm) += 1;
					state(tm) = 'F';
				}
				break;
			case 'C':
				if (!tape_cell(tm)) {
					tape_cell(tm) = true;
					position(tm) -= 1;
					state(tm) = 'D';
				} else {
					tape_cell(tm) = false;
					position(tm) += 1;
					state(tm) = 'B';
				}
				break;
			case 'D':
				if (!tape_cell(tm)) {
					tape_cell(tm) = true;
					position(tm) += 1;
					state(tm) = 'E';
				} else {
					tape_cell(tm) = false;
					position(tm) -= 1;
					state(tm) = 'C';
				}
				break;
			case 'E':
				if (!tape_cell(tm)) {
					tape_cell(tm) = true;
					position(tm) -= 1;
					state(tm) = 'A';
				} else {
					tape_cell(tm) = false;
					position(tm) += 1;
					state(tm) = 'D';
				}
				break;
			case 'F':
				if (!tape_cell(tm)) {
					tape_cell(tm) = true;
					position(tm) += 1;
					state(tm) = 'A';
				} else {
					tape_cell(tm) = true;
					position(tm) += 1;
					state(tm) = 'C';
				}
				break;
			default:
				assert(false);
		}
	}
	
	auto operator()() const {
		TM tm = std::make_tuple(std::vector<bool>(), 0, 'A');
		for (int i = 0; i < 12523873; ++i) {
			step(tm);
		}
		return checksum(tm);
	}
};
