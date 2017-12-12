#pragma once

#include "../utils/parser.h"

#include <map>
#include <regex>
#include <set>
#include <string>
#include <tuple>
#include <vector>

template<>
struct solve<12> {
	//static auto solution() {
	//	return std::make_pair(743, 1493);
	//}
	
	void addEdge(std::vector<std::vector<std::size_t>>& graph, std::size_t src, std::size_t dst) const {
		while (graph.size() <= src) graph.emplace_back();
		graph[src].emplace_back(dst);
	}
	
	
	const std::string input = "2017/12.input";
	auto operator()() const {
		auto lines = read_file_linewise(input);
		std::vector<std::vector<std::size_t>> graph;
		std::set<std::size_t> nodes;
		
		std::regex linere("([0-9]+) <-> ([0-9, ]+)");
		std::smatch match;
		for (const auto& line: lines) {
			if (std::regex_match(line, match, linere)) {
				std::size_t src = std::stoul(match[1]);
				nodes.insert(src);
				for (const auto& dsts: split(match.str(2), ", ")) {
					std::size_t dst = std::stoul(dsts);
					addEdge(graph, src, dst);
					addEdge(graph, dst, src);
					nodes.insert(dst);
				}
			} else {
				assert(false);
			}
		}
		
		int groups = 0;
		int group0size = 0;
		
		while (!nodes.empty()) {
			std::vector<std::size_t> queue;
			std::set<std::size_t> group;
			queue.emplace_back(*nodes.begin());
			while (!queue.empty()) {
				auto id = queue.back();
				queue.pop_back();
				nodes.erase(id);
				auto res = group.insert(id);
				if (!res.second) continue;
				if (graph.size() <= id) continue;
				for (auto dst: graph[id]) {
					queue.emplace_back(dst);
				}
			}
			if (group.find(0) != group.end()) group0size = group.size();
			++groups;
		}
		
		return std::make_pair(group0size, groups);
	}
};
