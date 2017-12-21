#pragma once

#include "../utils/parser.h"

#include <optional>
#include <queue>
#include <regex>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

template<>
struct solve<18> {
	static auto solution() {
		return std::make_pair(8600, 7239);
	}
	
	const std::string input = "2017/18.input";
	const std::regex linere = std::regex("(add|jgz|mod|mul|rcv|set|snd) ([a-z]|[-0-9]+) ?([a-z]|[-0-9]+)?");
	
	struct Data {
		std::array<long,26> data;
		Data() { data.fill(0); }
		long operator()(const std::variant<char,long>& v) const {
			return std::visit([*this](auto c) -> long {
				using T = decltype(c);
				if constexpr(std::is_same<T,char>::value) {
					return this->data[c - 'a'];
				} else {
					return c;
				}
			}, v);
		}
		void set(const std::variant<char,long>& c, long i) {
			data[std::get<char>(c) - 'a'] = i;
		}
	};
	using Operation = std::tuple<std::string,std::variant<char,long>,std::optional<std::variant<char,long>>>;
	
	std::variant<char,long> parse(const std::string& s) const {
		if (s == "") return 0l;
		if (s[0] >= 'a' && s[0] <= 'z') return s[0];
		return std::stol(s);
	}
	
	int simple_run(const std::vector<Operation>& ops) const {
		Data data;
		int cur = 0;
		long last_snd = 0;
		while (cur >= 0 && cur < ops.size()) {
			auto [op,a1,a2] = ops[cur];
			if (op == "add") {
				data.set(a1, data(a1) + data(*a2));
				++cur;
			} else if (op == "jgz") {
				if (data(a1) > 0) {
					cur += data(*a2);
				} else ++cur;
			} else if (op == "mod") {
				data.set(a1, data(a1) % data(*a2));
				++cur;
			} else if (op == "mul") {
				data.set(a1, data(a1) * data(*a2));
				++cur;
			} else if (op == "rcv") {
				if (data(a1) != 0) {
					return last_snd;
				}
				++cur;
			} else if (op == "set") {
				data.set(a1, data(*a2));
				++cur;
			} else if (op == "snd") {
				last_snd = data(a1);
				++cur;
			}
		}
	}
	
	bool doStep(const std::vector<Operation>& ops, int& cur, Data& data, std::queue<long>& in, std::queue<long>& out, int& send) const {
		if (cur < 0 || cur >= ops.size()) return false;
		
		auto [op,a1,a2] = ops[cur];
		if (op == "add") {
			data.set(a1, data(a1) + data(*a2));
			++cur;
		} else if (op == "jgz") {
			if (data(a1) > 0) {
				cur += data(*a2);
			} else ++cur;
		} else if (op == "mod") {
			data.set(a1, data(a1) % data(*a2));
			++cur;
		} else if (op == "mul") {
			data.set(a1, data(a1) * data(*a2));
			++cur;
		} else if (op == "rcv") {
			if (in.empty()) return false;
			data.set(a1, in.front());
			in.pop();
			++cur;
		} else if (op == "set") {
			data.set(a1, data(*a2));
			++cur;
		} else if (op == "snd") {
			out.push(data(a1));
			++send;
			++cur;
		}
		return true;
	}
	
	int parallel_run(const std::vector<Operation>& ops) const {
		std::array<std::queue<long int>,2> q;
		std::array<Data,2> d;
		std::array<int,2> cur({0,0});
		std::array<int,2> send({0,0});
		
		d[0].set('p', 0);
		d[1].set('p', 1);
		
		bool progress = true;
		int i = 0;
		while (progress) {
			progress = false;
			if (doStep(ops, cur[0], d[0], q[0], q[1], send[0])) progress = true;
			if (doStep(ops, cur[1], d[1], q[1], q[0], send[1])) progress = true;
		}
		return send[1];
	}
	
	auto operator()() const {
		std::vector<Operation> ops;
		for (const auto& d: read_file_linewise(input)) {
			if (std::smatch match; std::regex_match(d, match, linere)) {
				if (match.size() == 2) {
					ops.emplace_back(match[1], parse(match[2]), std::nullopt);
				} else {
					ops.emplace_back(match[1], parse(match[2]), parse(match[3]));
				}
			} else assert(false);
		}
		return std::make_pair(simple_run(ops), parallel_run(ops));
	}
};
