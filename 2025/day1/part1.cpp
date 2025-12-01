#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

constexpr uint8_t MaxValue = 99;

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;
	uint16_t Value = 50;
	size_t Result = 0;

	FileContent << File.rdbuf();

	while(std::getline(FileContent, Line, '\n')) {
		bool Clockwise = Line[0] == 'R';
		uint16_t Amount = std::stoi(Line.substr(1));
		int16_t TmpValue = 0;

		if(Clockwise) {
			TmpValue = (int16_t)Value + (int16_t)Amount;
		} else {
			TmpValue = (int16_t)Value - (int16_t)Amount;
		}

		if(TmpValue >= 0) {
			Value = TmpValue % (MaxValue + 1);
		} else {
			Value = ((TmpValue % (MaxValue + 1)) + (MaxValue + 1)) % (MaxValue + 1);
		}

		if(Value == 0) {
			++Result;
		}
	}

	std::cout << "result: " << Result << "\n";
}
