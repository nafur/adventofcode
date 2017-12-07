#pragma once

#include <fstream>

struct Dot {
	std::ofstream out;
	
	Dot(const std::string& filename): out(filename) {
		out << "digraph {" << std::endl;
	}
	~Dot() {
		out << "}" << std::endl;
	}
	
	void raw(const std::string& s) {
		out << '\t' << s << ';' << std::endl;
	}
	void node(const std::string& name, const std::string& label = "") {
		out << '\t' << name << " [label=\"" << label << "\"];" << std::endl;
	}
	void edge(const std::string& src, const std::string& target) {
		out << '\t' << src << " -> " << target << ";" << std::endl;
	}
};
