#pragma once

#include "../utils/parser.h"
#include "../utils/dot.h"

#include <map>
#include <regex>
#include <string>
#include <vector>

template<>
struct solve<7> {
	static auto solution() {
		return std::make_pair("aapssr"s, 1458);
	}
	
	using Tree = std::map<std::string, std::pair<int, std::vector<std::string>>>;
	
	//mutable Dot dot = Dot("tree.dot");
	
	std::string getRoot(const Tree& tree) const {
		Tree t = tree;
		// List of nodes that are not the root and can be removed
		std::vector<std::string> removal;
		while (true) {
			if (removal.empty()) {
				// Find new non-root nodes
				for (auto& elem: t) {
					if (elem.second.second.empty()) continue;
					for (const auto& child: elem.second.second) {
						if (t.find(child) != t.end()) {
							removal.push_back(child);
						}
					}
					if (!removal.empty()) {
						break;
					} else {
						elem.second.second.clear();
					}
				}
			}
			if (removal.empty()) break;
			std::string cur = removal.back();
			removal.pop_back();
			auto it = t.find(cur);
			if (it == t.end()) continue;
			removal.insert(removal.end(), it->second.second.begin(), it->second.second.end());
			t.erase(it);
		}
		assert(t.size() == 1);
		return t.begin()->first;
	}
	
	
	std::pair<std::string,bool> majority(const std::map<std::string,int>& v) const {
		std::map<int,int> m;
		for (const auto& i: v) m[i.second] += 1;
		if (m.size() == 0) return std::make_pair("",false);
		if (m.size() == 1) return std::make_pair(v.begin()->first, true);
		std::string max = v.begin()->first;
		int maxval = v.begin()->second;
		for (const auto& elem: m) {
			if (elem.second > m[maxval]) max = elem.first;
		}
		return std::make_pair(max, false);
	}
	
	// returns <actual weight, corrected weight>
	std::pair<int,int> computeWeight(const Tree& tree, const std::string& root) const {
		auto it = tree.find(root);
		if (it->second.second.empty()) {
			//dot.node(root, root + "\n(" + std::to_string(it->second.first) + ")");
			return std::make_pair(it->second.first, -1);
		}
		std::map<std::string,int> weights;
		for (const auto& child: it->second.second) {
			//dot.edge(child, root);
			auto res = computeWeight(tree, child);
			if (res.second != -1) return std::make_pair(-1, res.second);
			weights.emplace(child, res.first);
		}
		auto maj = majority(weights);
		if (!maj.second) {
			int weight = weights[maj.first];
			for (const auto& w: weights) {
				if (w.second != weight) {
					int error = w.second - weight;
					return std::make_pair(-1, tree.find(w.first)->second.first - error);
				}
			}
		}
		int weight = weights.begin()->second;
		//dot.node(root, root + "\n(" + std::to_string(it->second.first) + " -> " + std::to_string(weights.size() * weight + it->second.first) + ")");
		return std::make_pair(weights.size() * weight + it->second.first, -1);
	}
	
	const std::string input = "2017/7.input";
	auto operator()() const {
		//dot.raw("rankdir=LR");
		Tree tree;
		
		auto lines = read_file_linewise(input);
		
		std::regex linere("([a-z-]+) \\(([0-9]+)\\)( -> )?([a-z, ]+)?");
		std::smatch match;
		for (const auto& line: lines) {
			if (std::regex_match(line, match, linere)) {
				if (match.size() > 3) {
					auto children = split(match[4].str(), ", ");
					tree.emplace(match[1], std::make_pair(std::stoi(match[2]), children));
				} else {
					tree.emplace(match[1], std::make_pair(std::stoi(match[2]), std::vector<std::string>()));
				}
			} else {
				assert(false);
			}
		}
		std::string root = getRoot(tree);
		auto res = std::make_pair(root, computeWeight(tree, root).second);
		return res;
	}
};
