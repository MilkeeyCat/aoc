#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Range {
	size_t From;
	size_t To;
};

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;
	std::vector<Range> Ranges;
	size_t Result = 0;

	FileContent << File.rdbuf();

	size_t Middle = FileContent.str().find("\n\n");
	std::stringstream RangesString(FileContent.str().substr(0, Middle));
	std::stringstream Indices(FileContent.str().substr(Middle + 2));

	while(std::getline(RangesString, Line, '\n')) {
		size_t Split = Line.find("-");
		std::string From = Line.substr(0, Split);
		std::string To = Line.substr(Split + 1);

		Ranges.push_back({std::stoul(From), std::stoul(To)});
	}

	while(std::getline(Indices, Line, '\n')) {
		size_t Index = std::stoul(Line);

		for(const Range &Range : Ranges) {
			if(Index >= Range.From && Index <= Range.To) {
				++Result;

				break;
			}
		}
	}

	std::cout << "result: " << Result << "\n";
}
