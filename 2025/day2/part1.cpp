#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>

inline bool isInvalid(size_t Value) {
	std::string StringValue = std::to_string(Value);
	const size_t Length = StringValue.length();
	const size_t HalfLength = Length / 2;

	return Length % 2 == 0 && std::string_view(StringValue.data(), HalfLength) == std::string_view(StringValue.data() + HalfLength, HalfLength);
}

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Range;
	size_t Result = 0;

	FileContent << File.rdbuf();

	while(std::getline(FileContent, Range, ',')) {
		size_t Position = Range.find('-');
		size_t Start = std::stoull(Range.substr(0, Position));
		size_t End = std::stoull(Range.substr(Position + 1));

		for(size_t Value = Start; Value <= End; ++Value) {
			if(isInvalid(Value)) {
				Result += Value;
			}
		}
	}

	std::cout << "result: " << Result << "\n";
}
