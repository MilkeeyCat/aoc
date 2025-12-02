#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

inline bool isInvalid(size_t Value) {
	std::string StringValue = std::to_string(Value);
	const size_t Length = StringValue.length();

	if(Length < 2) {
		return false;
	}

	for(size_t N = 1; N < Length; ++N) {
		if(Length % N != 0 || Length / N < 2) {
			continue;
		}

		std::vector<std::string_view> Parts(Length / N);

		for(size_t I = 0; I < Parts.size(); ++I) {
			Parts[I] = std::string_view(StringValue.data() + I * N, N);
		}

		if(std::adjacent_find(Parts.begin(), Parts.end(), std::not_equal_to<>()) == Parts.end()) {
			return true;
		}
	}

	return false;
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
