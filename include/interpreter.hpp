#include <vector>
#include <string>

class Interpreter {
	public:

	std::vector<int> Cells = std::vector<int>();

	int Pointer;

	int Frozen = -15;

	int FrozenValue;

	void Run(std::string code);

	void Set(int cell, int value);

	void Reset();

	Interpreter();
};