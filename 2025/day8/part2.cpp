#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct Vec3 {
	size_t X;
	size_t Y;
	size_t Z;

	double distance(const Vec3 &Other) const {
		return std::sqrt((X - Other.X) * (X - Other.X) + (Y - Other.Y) * (Y - Other.Y) + (Z - Other.Z) * (Z - Other.Z));
	}
};

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;

	FileContent << File.rdbuf();

	std::vector<Vec3 *> Points;
	std::multimap<double, std::pair<size_t, size_t>> Distances;

	while(std::getline(FileContent, Line, '\n')) {
		const size_t Comma1 = Line.find(',');
		const size_t Comma2 = Line.find_last_of(',');

		Points.push_back(new Vec3{
			std::stoul(Line.substr(0, Comma1).data()),
			std::stoul(Line.substr(Comma1 + 1, Comma2 - Comma1).data()),
			std::stoul(Line.substr(Comma2 + 1).data()),
		});
	}

	for(size_t I = 0; I < Points.size(); ++I) {
		for(size_t J = I + 1; J < Points.size(); ++J) {
			Vec3 *LHS = Points[I];
			Vec3 *RHS = Points[J];

			Distances.emplace(LHS->distance(*RHS), std::make_pair(I, J));
		}
	}

	std::vector<std::pair<size_t, size_t>> Edges;
	std::transform(Distances.begin(), Distances.end(), std::back_inserter(Edges), [](auto &Pair) { return Pair.second; });

	std::vector<size_t> Circuit(Points.size());

	for(size_t I = 0; I < Circuit.size(); ++I) {
		Circuit[I] = I;
	}

	for(const auto &Pair : Edges) {
		const size_t New = Circuit[Pair.first];
		const size_t Old = Circuit[Pair.second];

		if(New != Old) {
			for(size_t &Value : Circuit) {
				if(Value == Old) {
					Value = New;
				}
			}

			if(std::unordered_set(Circuit.begin(), Circuit.end()).size() == 1) {
				std::cout << "result: " << Points[Pair.first]->X * Points[Pair.second]->X << "\n";

				return 0;
			}
		}
	}
}
