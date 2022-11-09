#include <iostream>
#include <fstream>
#include <vector>

#include "../include/framework.hpp"

#include "../include/compiler/compiler.hpp"

// copied from internet because fuck cpp for not including it in stdlib
std::vector<std::string> split(std::string phrase, std::string delimiter){
    std::vector<std::string> list;
	
    std::string s = phrase;
	
    size_t pos = 0;
	
    std::string token;
	
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
		
        list.push_back(token);
		
        s.erase(0, pos + delimiter.length());
    }
	
    list.push_back(s);
	
    return list;
}

int main() {
	std::cout << "Enter code to compile (Ctrl+D on an empty line to submit):\n";
	
	std::string code = "";

	for (char c = getchar(); c != -1; c = getchar()) {
		code += c;
	}

	// code = " let i = 57; while (i > 47) { print i; i = i - 1; }";

	Compiler compiler = Compiler(code);
	
	std::ofstream out = std::ofstream("output.bf");
	
	std::string output = compiler.Compile();

	out << output << "\n";

	out.close();

	std::cout << "Success! Your compiled brainf* is in output.bf!\n\nOutput:\n";

	Interpreter interpreter = Interpreter();

	interpreter.Run(output);

	std::cout << "\n";

	return 0;
} 