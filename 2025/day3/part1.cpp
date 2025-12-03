#include <array>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Bank;
	size_t Result = 0;

	FileContent << File.rdbuf();

	while(std::getline(FileContent, Bank, '\n')) {
		std::array<size_t, 2> Joltage = {0};

		for(size_t I = 0; I < Bank.length(); ++I) {
			const uint8_t Battery = Bank[I] - '0';

			if(Joltage[0] < Battery && I < Bank.length() - 1) {
				Joltage[0] = Battery;
				Joltage[1] = 0;
			} else if(Joltage[1] < Battery) {
				Joltage[1] = Battery;
			}
		}

		Result += Joltage[0] * 10 + Joltage[1];
	}

	std::cout << "result: " << Result << "\n";
}
