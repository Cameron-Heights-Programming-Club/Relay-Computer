#include <bitset>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "assembleSystem.hpp"

void cleanString(std::string& instr) {
	size_t insert = 0;
	size_t lastChar = 0;
	bool charFound = false;
	size_t hasComment = instr.find("//");
	if (hasComment != std::string::npos) {
		instr.resize(hasComment);
	}
	for (char c : instr) {
		if (!charFound) {
			if (c == ' ' || c == '\t') {
				continue;
			} else {
				charFound = true;
			}
		}
		if (c != '\r') {
			instr[insert++] = c;
			if (c != ' ' && c != '\t' && c != '\n') {
				lastChar = insert;
			}
		}
	}
	instr.resize(lastChar);
}

int main(int argc, char** argv) {
	std::ifstream asmFile(argv[1]);
	std::string line;
	std::vector<std::string> instructions;
	while (getline(asmFile, line)) {
		cleanString(line);
		if (line.length() > 0) {
			instructions.push_back(line);
		}
	}
	asmFile.close();

	assembleSystem assembler { instructions, "program.mc" };

	return assembler.assemble();
}