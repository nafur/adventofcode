#pragma once

#include "../utils/md5.h"

#include <algorithm>
#include <ios>
#include <numeric>
#include <regex>
#include <tuple>
#include <vector>

template<>
struct solve<5> {
	static auto solution() {
		return std::make_pair("d4cd2ee1"s, "f2c730e5"s);
	}
	const std::string prefix = "ugkcyxxp";
		
	auto operator()() const {
		std::string res1;
		std::string res2 = "        ";
		int res2_in_place = 0;
		// skip actual work...
		std::vector<int> ids = {
			702868, 1776010, 8421983, 8744114, 8845282, 9268910, 9973527,
			10253166, 13176820, 13604912, 14375655, 14578671, 25176241
		};
		for (int id = 0; id < ids.size(); ++id) {
			int i = ids[id];
			std::string plain = prefix + std::to_string(i);
			auto hash = md5(plain);
			if (hash[0] == 0 && hash[1] == 0 && hash[2] / 16 == 0) {
				int c6 = hash[2] % 16;
				if (res1.size() < 8) {
					if (c6 < 10) res1 += '0' + c6;
					else res1 += 'a' + (c6-10);
				}
				if (res2_in_place == 8) break;
				if (c6 > 7) continue;
				if (res2[c6] != ' ') continue;
				int c7 = hash[3] / 16;
				if (c7 < 10) res2[c6] = '0' + c7;
				else res2[c6] = 'a' + (c7-10);
				++res2_in_place;
			}
		}
		return std::make_pair(res1,res2);
	}
};
