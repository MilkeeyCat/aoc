#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

inline void parse(std::stringstream &Input, std::vector<std::vector<bool>> &Grid) {
	std::string Line;

	while(std::getline(Input, Line, '\n')) {
		std::vector<bool> Row;

		for(const char Char : Line) {
			Row.push_back(Char == '@');
		}

		Grid.push_back(Row);
	}
}

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::vector<std::vector<bool>> Grid;
	size_t Result = 0;

	FileContent << File.rdbuf();

	parse(FileContent, Grid);

	for(size_t Y = 0; Y < Grid.size(); ++Y) {
		for(size_t X = 0; X < Grid[Y].size(); ++X) {
			size_t RollsCount = 0;

			for(int8_t DY = -1; DY <= 1; ++DY) {
				for(int8_t DX = -1; DX <= 1; ++DX) {
					if(DY == 0 && DX == 0) {
						continue;
					}

					int32_t NewY = (int32_t)Y + DY;
					int32_t NewX = (int32_t)X + DX;

					if(NewY >= 0 && NewY < Grid.size() && NewX >= 0 && NewX < Grid[NewY].size() && Grid[NewY][NewX]) {
						++RollsCount;
					}
				}
			}

			if(Grid[Y][X] && RollsCount < 4) {
				++Result;
			}
		}
	}

	std::cout << "result: " << Result << "\n";
}
