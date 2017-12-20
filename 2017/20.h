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
struct solve<20> {
	static auto solution() {
		return std::make_pair(91, 567);
	}
	
	const std::string input = "2017/20.input";
	const std::regex linere = std::regex("p=<(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)>, v=<(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)>, a=<(-?[0-9]+),(-?[0-9]+),(-?[0-9]+)>");
	
	using Data = std::tuple<int,int,int>;
	
	void add(Data& d, const Data& delta) const {
		std::get<0>(d) += std::get<0>(delta);
		std::get<1>(d) += std::get<1>(delta);
		std::get<2>(d) += std::get<2>(delta);
	}
	
	void step(Data& p, Data& v, const Data& a) const {
		add(v, a);
		add(p, v);
	}
	
	auto operator()() const {
		auto data = read_file_linewise(input);
		
		std::vector<std::tuple<Data,Data,Data>> particles;
		
		auto p = [&particles](std::size_t i){ return std::get<0>(particles[i]); };
		auto v = [&particles](std::size_t i){ return std::get<1>(particles[i]); };
		auto a = [&particles](std::size_t i){ return std::get<2>(particles[i]); };
		
		std::smatch match;
		for (const auto& line: data) {
			if (std::regex_match(line, match, linere)) {
				particles.emplace_back(
					std::make_tuple(std::stoi(match[1]), std::stoi(match[2]), std::stoi(match[3])),
					std::make_tuple(std::stoi(match[4]), std::stoi(match[5]), std::stoi(match[6])),
					std::make_tuple(std::stoi(match[7]), std::stoi(match[8]), std::stoi(match[9]))
				);
			} else {
				assert(false);
			}
		}
		
		auto abssum = [](const auto& d) {
			return std::abs(std::get<0>(d)) + std::abs(std::get<1>(d)) + std::abs(std::get<2>(d));
		};
		auto reorient = [](const auto& p, const auto& v) {
			Data res = p;
			if (std::get<0>(v) < 0) std::get<0>(res) *= -1;
			if (std::get<1>(v) < 0) std::get<1>(res) *= -1;
			if (std::get<2>(v) < 0) std::get<2>(res) *= -1;
			return res;
		};
		auto c1 = [abssum](const auto& a1, const auto& a2) {
			return abssum(a1) < abssum(a2);
		};
		
		std::size_t min = 0;
		for (std::size_t i = 0; i < particles.size(); ++i) {
			if (c1(a(i), a(min))) { min = i; continue; }
			if (c1(a(min), a(i))) continue;
			if (c1(reorient(a(i), v(i)), reorient(a(min), v(min)))) { min = i; continue; }
			if (c1(reorient(a(min), v(min)), reorient(a(i), v(i)))) continue;
			if (c1(reorient(v(i), p(i)), reorient(v(min), p(min)))) { min = i; continue; }
			if (c1(reorient(v(min), p(min)), reorient(v(i), p(i)))) continue;
		}
		
		auto cmplt = [](const auto& a, const auto& b) {
			return std::get<0>(a) < std::get<0>(b);
		};
		auto cmpeq = [](const auto& a, const auto& b) {
			return std::get<0>(a) == std::get<0>(b);
		};
		for (int i = 0; i < 40; ++i) {
			std::sort(particles.begin(), particles.end(), cmplt);
			for (auto it = particles.begin(); it != std::prev(particles.end());) {
				auto next = std::next(it);
				if (cmpeq(*it, *next)) {
					while (cmpeq(*it, *next)) {
						next = particles.erase(next);
					}
					it = particles.erase(it);
				} else {
					++it;
				}
			}
			for (auto& p: particles) {
				step(std::get<0>(p), std::get<1>(p), std::get<2>(p));
			}
		}
		return std::make_pair<int,int>(min, particles.size());
	}
};
