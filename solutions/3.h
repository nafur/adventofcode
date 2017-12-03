#pragma once

template<>
struct solve<3> {
	static auto solution() {
		return std::make_pair(419,295229);
	}
	
	static constexpr int n = 289326;
	
	int level_size(int n) const {
		if (n == 0) return 1;
		return (2*n+1)*(2*n+1) - (2*n-1)*(2*n-1);
	}
	int level_start(int n) const {
		int res = 1;
		for (int level = 0; level < n; ++level) {
			res += level_size(level);
		}
		return res;
	}
	int level(int n) const {
		for (int level = 0; ; ++level) {
			int cursize = level_size(level);
			if (n <= cursize) return level;
			n -= cursize;
		}
	}
	
	std::pair<int,int> pos(int n) const {
		if (n == 1) return std::make_pair(0,0);
		
		int lvl = level(n);
		int offset = n - level_start(lvl);
		
		if (offset < 2*lvl) {
			return std::make_pair(lvl, offset - (lvl-1));
		} else if (offset < 4*lvl) {
			return std::make_pair(-offset + (3*lvl-1), lvl);
		} else if (offset < 6*lvl) {
			return std::make_pair(-lvl, -offset + (5*lvl-1));
		} else {
			return std::make_pair(offset - (7*lvl-1), -lvl);
		}
	}
	
	int distance(int n) const {
		auto p = pos(n);
		return std::abs(p.first) + std::abs(p.second);
	}
	
	std::vector<std::vector<int>> grow_grid(const std::vector<std::vector<int>>& grid) const {
		std::size_t new_size = grid.size() + 2;
		std::vector<std::vector<int>> res;
		res.emplace_back(new_size, 0);
		for (const auto& line: grid) {
			std::vector<int> new_line(1, 0);
			new_line.insert(new_line.end(), line.begin(), line.end());
			new_line.push_back(0);
			res.push_back(std::move(new_line));
		}
		res.emplace_back(new_size, 0);
		return res;
	}
	
	int spiral_sum(int n) const {
		std::vector<std::vector<int>> data(3, std::vector<int>(3, 0));
		auto elem = [&data](int lvl, int x, int y) -> int& {
			return data[x+lvl][y+lvl];
		};
		int lvl = 1;
		elem(lvl,0,0) = 1;
		int cur = 1;
		while (true) {
			cur++;
			if (level(cur)+1 > lvl) {
				data = grow_grid(data);
				lvl = level(cur)+1;
			}
			auto p = pos(cur);
			int x = p.first;
			int y = p.second;
			
			elem(lvl,x,y) = 
				elem(lvl,x+1,y) + elem(lvl,x+1,y+1) +
				elem(lvl,x,y+1) + elem(lvl,x-1,y+1) +
				elem(lvl,x-1,y) + elem(lvl,x-1,y-1) +
				elem(lvl,x,y-1) + elem(lvl,x+1,y-1);
			if (elem(lvl,x,y) > n) return elem(lvl,x,y);
		}
	}
	
	auto operator()() const {
		return std::make_pair(distance(n), spiral_sum(n));
	}
};
