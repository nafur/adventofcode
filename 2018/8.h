#pragma once

#include "../utils/parser.h"

#include <algorithm>
#include <cassert>
#include <charconv>

namespace task8 {
	struct Node {
		std::vector<Node> nodes;
		std::vector<int> meta;

		int count_meta() const {
			int res = std::accumulate(meta.begin(), meta.end(), 0);
			for (const auto& n: nodes) res += n.count_meta();
			return res;
		}
		int value() const {
			if (nodes.empty()) {
				return std::accumulate(meta.begin(), meta.end(), 0);
			}
			int sum = 0;
			for (int i: meta) {
				if (i <= 0) continue;
				if (i > nodes.size()) continue;
				sum += nodes[i - 1].value();
			}

			return sum;
		}
	};
}

template<>
struct solve<8> {
	static auto solution() {
		return std::make_pair(40309, 28779);
	}

	template<typename It>
	int next_value(It& pos, It end) const {
		int val = 0;
		pos = std::from_chars(pos, end, val).ptr;
		++pos;
		return val;
	}

	template<typename It>
	void parse_node(task8::Node& node, It& pos, It end) const {
		int nodes = next_value(pos, end);
		int metas = next_value(pos, end);
		for (int n = 0; n < nodes; ++n) {
			node.nodes.emplace_back();
			parse_node(node.nodes.back(), pos, end);
		}
		for (int m = 0; m < metas; ++m) {
			node.meta.emplace_back(next_value(pos, end));
		}
	}

	const std::string input = "2018/8.input";
	auto operator()() const {
		auto data = read_file(input);

		auto start = data.c_str();
		auto end = start + data.size();
		task8::Node root;
		parse_node(root, start, end);
		
		return std::make_pair(root.count_meta(), root.value());
	}
};
