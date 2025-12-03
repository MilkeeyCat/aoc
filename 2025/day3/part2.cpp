#include <algorithm>
#include <array>
#include <cstdint>
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
		std::array<uint8_t, 12> Joltage = {0};

		for(size_t I = 0; I < Bank.length(); ++I) {
			const uint8_t Battery = Bank[I] - '0';

			for(size_t J = 0; J < Joltage.size(); ++J) {
				if(Battery > Joltage[J] && Bank.length() - I >= Joltage.size() - J) {
					Joltage[J] = Battery;
					std::fill(Joltage.begin() + J + 1, Joltage.end(), 0);

					break;
				}
			}
		}

		size_t Value = 0;

		for(const size_t Battery : Joltage) {
			Value = Value * 10 + Battery;
		}

		Result += Value;
	}

	std::cout << "result: " << Result << "\n";
}
