#pragma once

#include <algorithm>
#include <cassert>
#include <list>
#include <vector>
#include <vector>

namespace task9 {


template<typename T>
struct allocator {

	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = T*;
	using const_pointer = const T*;
	using reference = T&;
	using const_reference = const T&;
	using value_type = T;

	static constexpr std::size_t blocksize = (1024 * 1024) / sizeof(T);

	struct buffer {
		uint8_t data[sizeof(T) * blocksize];
		std::size_t next = 0;

		bool full() const {
			return next == blocksize;
		}
		pointer allocate() {
			return reinterpret_cast<pointer>(&data[sizeof(T) * next++]);
		}
	};

	std::vector<std::unique_ptr<buffer>> mPool;

	allocator() = default;
	template<typename TT>
	allocator(const allocator<TT>& ) {}

	pointer allocate(size_type n) {
		if (mPool.empty() || mPool.back()->full()) {
			mPool.emplace_back(std::make_unique<buffer>());
		}
		return mPool.back()->allocate();
	}
	void deallocate(pointer p, size_type n) {}
};

}

template<>
struct solve<9> {

	using State = std::list<int, task9::allocator<int>>;

	static auto solution() {
		return std::make_pair(390093ul, 3150377341ul);
	}

	template<typename T, typename It>
	void circular_next(T& list, It& cur, std::size_t n) const {
		for (std::size_t k = 0; k < n; ++k) {
			++cur;
			if (cur == list.end()) cur = list.begin();
		}
	}
	template<typename T, typename It>
	void circular_prev(T& list, It& cur, std::size_t n) const {
		for (std::size_t k = 0; k < n; ++k) {
			if (cur == list.begin()) cur = list.end();
			--cur;
		}
	}

	template<typename It>
	void regular_step(State& state, It& cur, std::size_t marble) const {
		circular_next(state, cur, 2);
		cur = state.insert(cur, marble);
	}
	template<typename It>
	int weird_step(State& state, It& cur, std::size_t marble) const {
		circular_prev(state, cur, 7);
		marble += *cur;
		cur = state.erase(cur);
		return marble;
	}

	std::size_t winning_score_2(std::size_t elves, std::size_t count) const {
		std::size_t cur_elf = 0;
		std::vector<std::size_t> scores(elves, 0);
		State state = { 0 };
		auto cur = state.begin();
		for (std::size_t c = 1; c <= count; ++c) {
			//std::cout << state << " at " << *cur << std::endl;
			if (c % 23 == 0) {
				auto to_add = weird_step(state, cur, c);
				scores[cur_elf] += to_add;
			} else {
				regular_step(state, cur, c);
			}
			cur_elf = (cur_elf + 1) % elves;
		}
		return *std::max_element(scores.begin(), scores.end());
	}
	
	auto operator()() const {
		//assert(winning_score_2(9, 25) == 32);
		//assert(winning_score_2(10, 1618) == 8317);
		//assert(winning_score_2(471, 72026) == 390093);
		return std::make_pair(
			winning_score_2(471, 72026),
			winning_score_2(471, 7202600)
		);
	}
};
