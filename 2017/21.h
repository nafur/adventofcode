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
struct solve<21> {
	static auto solution() {
		return std::make_pair(197, 3081737);
	}
	
	const std::string input = "2017/21.input";
	
	using SmallMap = std::unordered_map<std::bitset<4>,std::bitset<9>>;
	using BigMap = std::unordered_map<std::bitset<9>,std::bitset<16>>;
	using Data = std::vector<std::vector<bool>>;
	
	const std::regex linere = std::regex("([.#/]+) => ([.#/]+)");
	
	static Data empty(int size) {
		Data res;
		for (int i = 0; i < size; ++i) {
			res.emplace_back(size);
		}
		return res;
	}
	
	template<std::size_t N>
	struct Operator {
		template<typename Map>
		void parseLine(Map& map, const std::string& from, const std::string& to) const {
			std::bitset<N*N> f;
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j)
					f[i*N+j] = (from[i*(N+1)+j] == '#');
			std::bitset<(N+1)*(N+1)> t;
			for (int i = 0; i < N+1; ++i)
				for (int j = 0; j < N+1; ++j)
					t[i*(N+1)+j] = (to[i*(N+2)+j] == '#');
			map.emplace(f, t);
		}
		
		std::bitset<N*N> extract(const Data& d, int x, int y) const {
			std::bitset<N*N> res;
			for (int i = 0; i < N; ++i)
				for (int j = 0; j < N; ++j)
					res[j*N+i] = d[y+j][x+i];
			return res;
		}
		void restore(Data& d, const std::bitset<(N+1)*(N+1)>& repl, int x, int y) const {
			for (int i = 0; i < N+1; ++i)
				for (int j = 0; j < N+1; ++j)
					d[y+j][x+i] = repl[j*(N+1)+i];
		}
		
		std::bitset<N*N> rotate(const std::bitset<N*N>& b) const {
			std::bitset<N*N> res;
			for (int y = 0; y < N; ++y) {
				for (int x = 0; x < N; ++x) {
					// y == 0: [(0,2),(0,1)(0,0)]
					// y == 1: [(1,2),(1,1)(1,0)]
					// y == 2: [(2,2),(2,1)(2,0)]
					int nx = y;
					int ny = N-x-1;
					res[y*N+x] = b[ny*N+nx];
				}
			}
			return res;
		}
		std::bitset<N*N> flip(const std::bitset<N*N>& b) const {
			std::bitset<N*N> res;
			for (int y = 0; y < N; ++y) {
				for (int x = 0; x < N; ++x) {
					res[y*N+x] = b[x*N+y];
				}
			}
			return res;
		}
		
		template<typename Map>
		auto mapresult(const Map& m, std::bitset<N*N> in) const {
			for (int i = 0; i < 4; ++i) {
				auto it = m.find(in);
				if (it != m.end()) return it->second;
				auto it2 = m.find(flip(in));
				if (it2 != m.end()) return it2->second;
				in = rotate(in);
			}
			assert(false);
			return std::bitset<(N+1)*(N+1)>();
		}
		std::size_t enlarge(std::size_t n) const {
			if (N == 2) return (n/2) * 3;
			else return (n/3) * 4;
		}
		
		template<typename Map>
		Data step(const Data& d, const Map& map) const {
			Data res = empty(enlarge(d.size()));
			for (int x = 0; x < d.size(); x += N) {
				for (int y = 0; y < d.size(); y += N) {
					auto rep = mapresult(map, extract(d, x, y));
					restore(res, rep, enlarge(x), enlarge(y));
				}
			}
			return res;
		}
	};
	
	Operator<2> op2;
	Operator<3> op3;
	
	Data step(const Data& d, const SmallMap& small, const BigMap& big) const {
		if (d.size() % 2 == 0) {
			return op2.step(d, small);
		} else {
			return op3.step(d, big);
		}
	}
	
	int count(const Data& d) const {
		return std::accumulate(d.begin(), d.end(), 0, [](int a, const auto& b) {
			return std::accumulate(b.begin(), b.end(), a, [](int a, const auto& b) {
				return a + (b ? 1 : 0);
			});
		});
	}
	
	auto operator()() const {
		SmallMap small;
		BigMap big;
		for (const auto& line: read_file_linewise(input)) {
			if (std::smatch match; std::regex_match(line, match, linere)) {
				if (match.str(1).size() == 5) {
					op2.parseLine(small, match[1], match[2]);
				} else {
					op3.parseLine(big, match[1], match[2]);
				}
			} else {
				assert(false);
			}
		}
		Data data({{false, true, false}, {false, false, true}, {true, true, true}});
		
		for (int i = 0; i < 5; ++i) {
			data = step(data, small, big);
		}
		int res1 = count(data);
		for (int i = 5; i < 18; ++i) {
			data = step(data, small, big);
		}
		int res2 = count(data);
		
		return std::make_pair(res1, res2);
	}
};
