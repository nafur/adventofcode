#pragma once

#include <string>

int sum_if_same(const std::string& sv, std::size_t offset) {
	int sum = 0;
	for (std::size_t cur = 0; cur < sv.size(); ++cur) {
		std::size_t other = (cur + offset) % sv.size();
		if (sv[cur] == sv[other]) sum += sv[cur] - '0';
	}
	return sum;
}
