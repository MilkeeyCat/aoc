#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

struct Range {
	size_t From;
	size_t To;

	bool operator==(const Range &Other) const {
		return From == Other.From && To == Other.To;
	}

	bool overlaps(const Range &Other) const {
		return (From >= Other.From && From <= Other.To) || (To >= Other.From && To <= Other.To);
	}
};

void mergeRanges(std::vector<Range> &Ranges) {
	std::optional<size_t> MergedIndex;

	for(size_t I = 0; I < Ranges.size() && !MergedIndex.has_value(); ++I) {
		const Range &MergeCandidate = Ranges[I];

		for(size_t J = 0; J < Ranges.size() && !MergedIndex.has_value(); ++J) {
			if(I == J) {
				continue;
			}

			Range &Range = Ranges[J];

			if(MergeCandidate.overlaps(Range)) {
				Range.From = std::min(Range.From, MergeCandidate.From);
				Range.To = std::max(Range.To, MergeCandidate.To);
				MergedIndex = I;
			} else if(MergeCandidate == Range) {
				MergedIndex = I;
			}
		}
	}

	if(MergedIndex.has_value()) {
		Ranges.erase(Ranges.begin() + *MergedIndex);
		mergeRanges(Ranges);
	}
}

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;
	std::vector<Range> Ranges;
	size_t Result = 0;

	FileContent << File.rdbuf();

	size_t Middle = FileContent.str().find("\n\n");
	std::stringstream RangesString(FileContent.str().substr(0, Middle));

	while(std::getline(RangesString, Line, '\n')) {
		size_t Split = Line.find("-");
		std::string From = Line.substr(0, Split);
		std::string To = Line.substr(Split + 1);

		Ranges.push_back({std::stoul(From), std::stoul(To)});
	}

	mergeRanges(Ranges);

	for(const Range &Range : Ranges) {
		Result += Range.To - Range.From + 1;
	}

	std::cout << "result: " << Result << "\n";
}
