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
struct solve<23> {
	static auto solution() {
		return std::make_pair(6724, 903);
	}
	
	const std::string input = "2017/23.input";
	const std::regex linere = std::regex("(jnz|mul|set|sub) ([a-z]|[-0-9]+) ?([a-z]|[-0-9]+)?");
	
	struct Data {
		std::array<long,8> data;
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
		int mulcnt = 0;
		while (cur >= 0 && cur < ops.size()) {
			auto [op,a1,a2] = ops[cur];
			if (op == "jnz") {
				if (data(a1) != 0) {
					cur += data(*a2);
				} else ++cur;
			} else if (op == "mul") {
				data.set(a1, data(a1) * data(*a2));
				++cur;
				++mulcnt;
			} else if (op == "set") {
				data.set(a1, data(*a2));
				++cur;
			} else if (op == "sub") {
				data.set(a1, data(a1) - data(*a2));
				++cur;
			}
		}
		return mulcnt;
	}
	
	int value_of_h() const {
		int b = 84 * 100 + 100000;
		int c = b + 17000;
		int h = 0;
		while (b <= c) {
			bool f = false;
			for (int d = 2; d < b && !f; ++d) {
				if (b % d == 0) f = true;
			}
			if (f) ++h;
			b += 17;
		}
		return h;
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
		return std::make_pair(simple_run(ops), value_of_h());
	}
};
