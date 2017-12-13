#pragma once

#include "../utils/parser.h"

#include <regex>
#include <vector>

template<>
struct solve<13> {
	static auto solution() {
		return std::make_pair(1300, 3870382);
	}
	
	int severity(const std::vector<int>& firewall, int delay = 0) const {
		int severity = -1;
		for (int cur = 0; cur < firewall.size(); ++cur) {
			if (firewall[cur] == 0) continue;
			int pos = (cur + delay) % (2 * (firewall[cur] - 1));
			if (pos == 0) {
				//std::cout << "Caught at " << cur << " with delay " << delay << std::endl;
				if (severity == -1) severity = 0;
				severity += cur * firewall[cur];
				if (delay > 0) break;
			}
		}
		return severity;
	}
	
	const std::string input = "2017/13.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<int> firewall;
		
		std::regex linere("([0-9]+): ([0-9]+)");
		std::smatch match;
		for (const auto& line: lines) {
			if (std::regex_match(line, match, linere)) {
				int level = std::stoi(match[1]);
				int depth = std::stoi(match[2]);
				while (firewall.size() <= level) firewall.emplace_back(0);
				firewall[level] = depth;
			} else {
				assert(false);
			}
		}
		
		int delay = 0;
		while (severity(firewall, delay) >= 0) {
			++delay;
		}
		
		return std::make_pair(severity(firewall), delay);
	}
};
