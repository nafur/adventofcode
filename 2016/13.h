#pragma once

#include <queue>
#include <tuple>
#include <vector>

template<>
struct solve<13> {
	static auto solution() {
		return std::make_pair(92, 124);
	}
	const std::size_t input = 1350;
	const int destx = 31;
	const int desty = 39;
	
	bool occupied(std::size_t x, std::size_t y) const {
		std::size_t tmp = x*x + 3*x + 2*x*y + y + y*y + input;
		int bits = __builtin_popcountll(tmp);
		return bits % 2 == 1;
	}
	int mindist(int x, int y) const {
		return std::abs(x - destx) + std::abs(y - desty);
	}
	bool wasThere(std::vector<std::vector<int>>& visited, int x, int y, int d) const {
		while (visited.size() <= y) visited.emplace_back();
		while (visited[y].size() <= x) visited[y].emplace_back(-1);
		if (visited[y][x] != -1 && visited[y][x] <= d) return true;
		visited[y][x] = d;
		return false;
	}
	
	int findShortest() const {
		using T = std::tuple<int,int,int,int>;
		std::priority_queue<T,std::vector<T>,std::greater<T>> queue;
		
		int curmin = 1000;
		queue.emplace(mindist(1,1),0,1,1);
		
		std::vector<std::vector<int>> visited;
		
		while (!queue.empty()) {
			auto [est,d,x,y] = queue.top();
			queue.pop();
			if (x < 0) continue;
			if (y < 0) continue;
			if (d >= curmin) continue;
			if (occupied(x,y)) continue;
			if (x == destx && y == desty) {
				curmin = d;
				continue;
			}
			if (d + mindist(x,y) >= curmin) {
				continue;
			}
			if (wasThere(visited, x, y, d)) continue;
			queue.emplace(mindist(x,y+1), d+1, x, y+1);
			queue.emplace(mindist(x,y-1), d+1, x, y-1);
			queue.emplace(mindist(x+1,y), d+1, x+1, y);
			queue.emplace(mindist(x-1,y), d+1, x-1, y);
		}
		return curmin;
	}
	
	int countReachable(int dist) const {
		using T = std::tuple<int,int,int>;
		std::vector<T> queue;
		
		queue.emplace_back(1,1,0);
		
		std::vector<std::vector<int>> visited;
		
		while (!queue.empty()) {
			auto [x,y,d] = queue.back();
			queue.pop_back();
			if (x < 0 || y < 0) continue;
			if (d > dist) continue;
			if (occupied(x,y)) continue;
			if (wasThere(visited, x, y, d)) continue;
			queue.emplace_back(x, y+1, d+1);
			queue.emplace_back(x, y-1, d+1);
			queue.emplace_back(x+1, y, d+1);
			queue.emplace_back(x-1, y, d+1);
		}
		int cnt = 0;
		for (int y = 0; y < visited.size(); ++y) {
			for (int x = 0; x < visited[y].size(); ++x) {
				if (visited[y][x] != -1) ++cnt;
			}
		}
		return cnt;
	}
	
	auto operator()() const {
		return std::make_pair(findShortest(), countReachable(50));
	}
};
