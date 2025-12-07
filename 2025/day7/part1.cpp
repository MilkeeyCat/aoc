#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;
	size_t Result = 0;

	FileContent << File.rdbuf();

	std::vector<bool> Beams(FileContent.str().find('\n'));

	while(std::getline(FileContent, Line, '\n')) {
		const size_t Length = Line.length();

		for(size_t I = 0; I < Length; ++I) {
			switch(Line[I]) {
			case 'S':
				Beams[I] = true;

				break;
			case '^':
				if(Beams[I]) {
					Beams[I] = false;
					++Result;
				}

				if(I > 0 && !Beams[I - 1]) {
					Beams[I - 1] = true;
				}

				if(I < Length - 1 && !Beams[I + 1]) {
					Beams[I + 1] = true;
				}

				break;
			}
		}
	}

	std::cout << "result: " << Result << "\n";
}
