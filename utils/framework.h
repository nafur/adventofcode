#pragma once

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std::string_literals;

template<std::size_t n>
struct solve {
	void operator()() const {}
};

template<std::size_t I = 0, typename... T, typename std::enable_if<I == sizeof...(T), void>::type* = nullptr>
inline std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& /*unused*/) {
	return os << ")";
}
template<std::size_t I = 0, typename... T, typename std::enable_if<I < sizeof...(T), void>::type* = nullptr>
std::ostream& operator<<(std::ostream& os, const std::tuple<T...>& t) {
	if (I == 0) os << "(" << std::get<I>(t);
	else os << ", " << std::get<I>(t);
	return operator<< <I+1>(os, t);
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1,T2>& p) {
	return os << "(" << p.first << ", " << p.second << ")";
}
template<typename T>
inline std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
	os << "[" << v.size() << ": ";
	bool first = true;
	for (const auto& t: v) {
		if (!first) os << ", ";
		first = false;
		os << t;
	}
	return os << "]";
}
template<typename T, std::size_t N>
inline std::ostream& operator<<(std::ostream& os, const std::array<T,N>& v) {
	os << "[" << N << ": ";
	bool first = true;
	for (const auto& t: v) {
		if (!first) os << ", ";
		first = false;
		os << t;
	}
	return os << "]";
}
template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::map<T1,T2>& m) {
	os << "{";
	bool first = true;
	for (const auto& t: m) {
		if (!first) os << ", ";
		first = false;
		os << t.first << ": " << t.second;
	}
	return os << "}";
}

template<typename> struct Void { using type = void; };
template<typename T, typename SFINAE = void>
struct has_solution : std::false_type {};
template<typename T>
struct has_solution<T, typename Void<decltype( T::solution )>::type> : std::true_type {}; 

template<std::size_t n>
void runSolver() {
	runSolver<n-1>();
	
	using Solver = solve<n>;
	std::cout << "***** Solving puzzle " << n << std::endl;
	if constexpr(std::is_same<decltype(Solver()()), void>::value) {
		std::cerr << "Solution for puzzle " << n << " has not yet been implemented." << std::endl;
	} else {
		Solver s;
		auto res = s();
		std::cout << "Solution: " << res << std::endl;
		if constexpr (has_solution<Solver>::value) {
			if (res == s.solution()) {
				std::cout << "Correct!" << std::endl;
			} else {
				std::cout << "Should be " << s.solution() << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

template<>
void runSolver<0>() {}
