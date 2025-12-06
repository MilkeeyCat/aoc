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
	size_t Number = 0;
	size_t StartIndex = 0;
	size_t RowEndIndex = 0;
	size_t CurrentIndex = 0;

	while(true) {
		switch(Input[CurrentIndex]) {
		case '*':
		case '+': {
			size_t ColumnResult = Input[CurrentIndex] == '*' ? 1 : 0;

			for(const size_t Number : Numbers) {
				ColumnResult = Input[CurrentIndex] == '*' ? ColumnResult * Number : ColumnResult + Number;
			}

			Numbers.clear();
			Result += ColumnResult;

			if(Input[RowEndIndex] == '\n') {
				goto end;
			}

			StartIndex = CurrentIndex = RowEndIndex;

			break;
		}
		case '\n':
		case ' ':
			if(Number == 0) {
				++CurrentIndex;
			} else {
				Numbers.push_back(Number);

				if(CurrentIndex % RowLength > RowEndIndex) {
					RowEndIndex = CurrentIndex % RowLength;
				}

				Number = 0;
				StartIndex = CurrentIndex = StartIndex + RowLength;
			}

			break;
		default:
			Number = Number * 10 + Input[CurrentIndex] - '0';
			++CurrentIndex;

			break;
		}
	}

end:

	std::cout << "result: " << Result << "\n";
}
