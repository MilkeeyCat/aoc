#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	size_t Result = 0;

	FileContent << File.rdbuf();

	std::string Input(FileContent.str());
	size_t RowLength = Input.find("\n") + 1;
	std::vector<size_t> Numbers;
	char LastOperationIndex = 0;

	for(size_t I = 0; I < RowLength + 1; ++I) {
		size_t Number = 0;

		for(size_t J = 0; J < (Input.length() / RowLength) - 1; ++J) {
			char Digit = Input[RowLength * J + I];

			if(Digit != ' ' && Digit != '\n') {
				Number = Number * 10 + Digit - '0';
			}
		}

		if(Number == 0) {
			char Operation = Input[Input.length() - RowLength + LastOperationIndex];

			while(Operation == ' ') {
				++LastOperationIndex;
				Operation = Input[Input.length() - RowLength + LastOperationIndex];
			}

			size_t ColumnResult = Operation == '*' ? 1 : 0;

			for(const size_t Number : Numbers) {
				ColumnResult = Operation == '*' ? ColumnResult * Number : ColumnResult + Number;
			}

			Numbers.clear();
			Result += ColumnResult;
			++LastOperationIndex;
		} else {
			Numbers.push_back(Number);
			Number = 0;
		}
	}

	std::cout << "result: " << Result << "\n";
}
