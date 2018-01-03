#pragma once

template<typename T>
struct InfiniteGrid {
	std::vector<std::vector<T>> mData;
	T& operator()(int x, int y) {
		std::size_t x2 = (x < 0 ? 2*std::abs(x)-1 : 2*x);
		std::size_t y2 = (y < 0 ? 2*std::abs(y)-1 : 2*y);
		while (mData.size() <= y2) {
			mData.emplace_back();
		}
		if (mData[y2].size() <= x2) {
			mData[y2].resize(x2+1, T());
		}
		return mData[y2][x2];
	}
	T& operator()(const std::pair<int,int>& pos) {
		return (*this)(pos.first, pos.second);
	}
};

template<typename T>
struct Grid {
	using Position = std::pair<std::size_t,std::size_t>;
	using Ref = typename std::vector<T>::reference;
	std::vector<std::vector<T>> mData;
	Ref operator()(std::size_t x, std::size_t y) {
		while (mData.size() <= y) {
			mData.emplace_back();
		}
		if (mData[y].size() <= x) {
			mData[y].resize(x+1, T());
		}
		return mData[y][x];
	}
	Ref operator()(const Position& pos) {
		return (*this)(pos.first, pos.second);
	}
	template<typename F>
	void apply(const Position& start, const Position& end, F&& f) {
		std::size_t minx = std::min(start.first, end.first);
		std::size_t maxx = std::max(start.first, end.first);
		std::size_t miny = std::min(start.second, end.second);
		std::size_t maxy = std::max(start.second, end.second);
		for (std::size_t x = minx; x <= maxx; ++x) {
			for (std::size_t y = miny; y <= maxy; ++y) {
				(*this)(x,y) = f((*this)(x,y));
			}
		}
	}
};
