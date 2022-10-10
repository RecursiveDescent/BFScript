#include <iostream>

#include "../include/interpreter.hpp"

void Interpreter::Run(std::string code) {
	std::vector<uint8_t> loops = std::vector<uint8_t>();
	
	for (int pos = 0; pos < code.length(); pos++) {
		char c = code[pos];

		if (c == '[') {
			std::string loop = "";

			int level = 1;

			while (level > 0 && pos < code.length()) {
				pos++;

				if (code[pos] == '[') {
					level++;
					
					loop += code[pos];

					continue;
				}

				if (code[pos] == ']') {
					level--;

					if (level > 0)
						loop += code[pos];

					continue;
				}

				loop += code[pos];
			}

			if (loop == "" && level > 0)
				break;

			int i = 0;

			while (Cells[Pointer] != 0 && i++ < 50000) {
				Run(loop);

				if (level > 0)
					break;
			}
		}
	
		if (c == '+')
			Cells[Pointer]++;
	
		if (c == '-')
			Cells[Pointer]--;
	
		if (c == '>') {
			Pointer++;

			if (Pointer >= Cells.size())
				Cells.push_back(0);
		}
	
		if (c == '<') {
			Pointer--;

			if (Pointer < 0) {
				break;
			}
		}
	
		if (c == ',')
			Cells[Pointer] = std::cin.get();
	
		if (c == '.')
			std::cout << Cells[Pointer];
	}
}

void Interpreter::Set(int cell, int value) {
	if (cell >= Cells.size()) {
		for (int i = 0; i < cell - Cells.size(); i++) {
			Cells.push_back(0);
		}
	}

	Cells[cell] = value;
}

void Interpreter::Reset() {
	Cells.clear();

	Pointer = 0;
}

Interpreter::Interpreter() {
	Cells.push_back(0);

	Pointer = 0;
}