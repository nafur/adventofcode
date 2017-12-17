#pragma once

#include "../utils/parser.h"

#include <cstdint>
#include <map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<16> {
	static auto solution() {
		return std::make_pair("hmefajngplkidocb"s, "fbidepghmjklcnoa"s);
	}
	
	const std::string input = "2017/16.input";
	
	const std::regex spinre = std::regex("s([0-9]+)");
	const std::regex exchangere = std::regex("x([0-9]+)/([0-9]+)");
	const std::regex partnerre = std::regex("p([a-z])/([a-z])");
	
	struct Dancer {
		using Step = std::uint16_t;
		static constexpr Step size = 16;
		std::vector<Step> mSteps;
		Step mDelta = 0;
		
		Step assemble(bool action, Step a, Step b) const {
			return static_cast<Step>(
				(action ? 0b100000000 : 0) |
				(a << 4) | b
			);
		}
		bool action(Step s) const {
			return (s & 0b100000000) != 0;
		}
		Step first(Step s) const {
			return (s & 0b011110000) >> 4;
		}
		Step second(Step s) const {
			return s & 0b01111;
		}
		
		void spin(Step delta) {
			assert(delta < size);
			mDelta = (mDelta + delta) % size;
		}
		void exchange(Step a, Step b) {
			mSteps.emplace_back(assemble(false, (a + size - mDelta) % size, (b + size - mDelta) % size));
		}
		void partner(Step a, Step b) {
			mSteps.emplace_back(assemble(true, a, b));
		}
		
		void apply(std::array<std::uint16_t,16>& pos, std::array<std::uint16_t,16>& lookup) const {
			for (Step s: mSteps) {
				if (action(s)) {
					Step a = first(s);
					Step b = second(s);
					std::swap(lookup[a], lookup[b]);
					pos[lookup[a]] = a;
					pos[lookup[b]] = b;
				} else {
					Step a = first(s);
					Step b = second(s);
					std::swap(pos[a], pos[b]);
					lookup[pos[a]] = a;
					lookup[pos[b]] = b;
				}
			}
			for (int i = 0; i < 16; ++i) {
				lookup[i] = (lookup[i] + mDelta) % 16;
				pos[lookup[i]] = i;
			}
		}
	};
	
	std::string print(const std::array<std::uint16_t,16>& a) const {
		std::string res;
		for (int i = 0; i < a.size(); ++i) {
			res += char('a' + a[i]);
		}
		return res;
	}
	
	auto operator()() const {
		auto data = split(read_file(input), ",");
		
		Dancer dancer;
		std::smatch match;
		for (const auto& d: data) {
			if (std::regex_match(d, match, spinre)) {
				dancer.spin(std::stoi(match[1]));
			} else if (std::regex_match(d, match, exchangere)) {
				dancer.exchange(std::stoi(match[1]), std::stoi(match[2]));
			} else if (std::regex_match(d, match, partnerre)) {
				dancer.partner(match.str(1)[0] - 'a', match.str(2)[0] - 'a');
			}
		}
		
		std::array<std::uint16_t,16> initial = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
		
		std::array<std::uint16_t,16> p = initial;
		std::array<std::uint16_t,16> l = initial;
		dancer.apply(p, l);
		std::string after_one = print(p);
		
		p = initial;
		l = initial;
		
		int first_hit = 0;
		for (int i = 1; i < 10000; ++i) {
			dancer.apply(p, l);
			if (p == initial) {
				first_hit = i;
				break;
			}
		}
		
		p = initial;
		l = initial;
		for (int i = 0; i < 1000000000 % first_hit; ++i) {
			dancer.apply(p, l);
		}
		std::string after_all = print(p);
		
		return std::make_pair(after_one, after_all);
	}
};
