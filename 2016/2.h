#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <string>

template<>
struct solve<2> {
	static auto solution() {
		return std::make_pair("74921"s, "A6B35"s);
	}
	const std::string input = "2016/2.input";
	
	struct Keypad1 {
		int current = 5;
		void move(char c) {
			switch (c) {
				case 'U': up(); break;
				case 'R': right(); break;
				case 'D': down(); break;
				case 'L': left(); break;
			}
		}
		void up() {
			if (current < 4) return;
			current -= 3;
		}
		void right() {
			if (current % 3 == 0) return;
			current += 1;
		}
		void down() {
			if (current > 6) return;
			current += 3;
		}
		void left() {
			if (current % 3 == 1) return;
			current -= 1;
		}
		char pos() const {
			return '0' + current;
		}
	};
	
	struct Keypad2 {
		char current = '5';
		void move(char c) {
			switch (c) {
				case 'U': up(); break;
				case 'R': right(); break;
				case 'D': down(); break;
				case 'L': left(); break;
			}
		}
		void up() {
			switch (current) {
				case '3': current = '1'; break;
				case '6': current = '2'; break;
				case '7': current = '3'; break;
				case '8': current = '4'; break;
				case 'A': current = '6'; break;
				case 'B': current = '7'; break;
				case 'C': current = '8'; break;
				case 'D': current = 'B'; break;
			}
		}
		void right() {
			switch (current) {
				case '2': current = '3'; break;
				case '3': current = '4'; break;
				case '5': current = '6'; break;
				case '6': current = '7'; break;
				case '7': current = '8'; break;
				case '8': current = '9'; break;
				case 'A': current = 'B'; break;
				case 'B': current = 'C'; break;
			}
		}
		void down() {
			switch (current) {
				case '1': current = '3'; break;
				case '2': current = '6'; break;
				case '3': current = '7'; break;
				case '4': current = '8'; break;
				case '6': current = 'A'; break;
				case '7': current = 'B'; break;
				case '8': current = 'C'; break;
				case 'B': current = 'D'; break;
			}
		}
		void left() {
			switch (current) {
				case '3': current = '2'; break;
				case '4': current = '3'; break;
				case '6': current = '5'; break;
				case '7': current = '6'; break;
				case '8': current = '7'; break;
				case '9': current = '8'; break;
				case 'B': current = 'A'; break;
				case 'C': current = 'B'; break;
			}
		}
		char pos() const {
			return current;
		}
	};
	
	template<typename Keypad, typename T>
	auto simulate(const T& lines) const {
		Keypad k;
		std::string code;
		for (const auto& l: lines) {
			for (auto c: l) k.move(c);
			code = code + k.pos();
		}
		return code;
	}
	auto operator()() const {
		auto lines = read_file_linewise(input);
		return std::make_pair(simulate<Keypad1>(lines), simulate<Keypad2>(lines));
	}
};
