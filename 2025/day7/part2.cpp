#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

uint32_t gimmeKey(size_t LineIndex, size_t Nth) {
	return (((uint32_t)LineIndex) << 16) | (((uint32_t)Nth) & 0x0000ffff);
}

size_t doTheMagicStuff(std::vector<std::string> &Diagram, size_t LineIndex, std::vector<bool> &Beams, std::unordered_map<uint32_t, size_t> &Memo) {
	size_t Result = 0;

	if(LineIndex == Diagram.size() - 1) {
		return 1;
	}

	const std::string &Line = Diagram[LineIndex];
	const size_t Length = Line.length();

	for(size_t I = 0; I < Length; ++I) {
		switch(Line[I]) {
		case 'S':
			Beams[I] = true;
			Result += doTheMagicStuff(Diagram, LineIndex + 1, Beams, Memo);

			break;
		case '^': {
			if(!Beams[I]) {
				continue;
			}

			Beams[I] = false;

			if(auto Entry = Memo.find(gimmeKey(LineIndex, I)); Entry != Memo.end()) {
				return Entry->second;
			}

			Beams[I - 1] = true;
			size_t LHS = doTheMagicStuff(Diagram, LineIndex + 1, Beams, Memo);
			Beams[I - 1] = false;
			Beams[I + 1] = true;
			size_t RHS = doTheMagicStuff(Diagram, LineIndex + 1, Beams, Memo);
			Beams[I + 1] = false;
			Memo[gimmeKey(LineIndex, I)] = LHS + RHS;
			Result += LHS + RHS;

			break;
		}
		default:
			if(Beams[I]) {
				Result += doTheMagicStuff(Diagram, LineIndex + 1, Beams, Memo);
			}

			break;
		}
	}

	return Result;
}

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;

	FileContent << File.rdbuf();

	std::vector<bool> Beams(FileContent.str().find('\n'));
	std::vector<std::string> Diagram;
	std::unordered_map<uint32_t, size_t> Memo;

	while(std::getline(FileContent, Line, '\n')) {
		Diagram.push_back(Line);
	}

	size_t Result = doTheMagicStuff(Diagram, 0, Beams, Memo);

	std::cout << "result: " << Result << "\n";
}
