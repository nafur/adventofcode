#include <iostream>

template<std::size_t n>
struct solve {
	void operator()() const {}
};

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
		auto res = Solver()();
		std::cout << "Solution: " << res << std::endl;
		if constexpr (has_solution<Solver>::value) {
			if (res == Solver::solution) {
				std::cout << "Correct!" << std::endl;
			} else {
				std::cout << "Should be " << Solver::solution << std::endl;
			}
		}
	}
	std::cout << std::endl;
}

template<>
void runSolver<0>() {}
