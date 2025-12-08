#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
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
	std::transform(Distances.begin(), std::next(Distances.begin(), 1000), std::back_inserter(Edges), [](auto &Pair) { return Pair.second; });

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
		}
	}

	std::map<size_t, size_t> Map;

	for(size_t Value : Circuit) {
		Map[Value]++;
	}

	std::vector<size_t> Result;

	std::transform(Map.begin(), Map.end(), std::back_inserter(Result), [](auto &Pair) { return Pair.second; });
	std::sort(Result.begin(), Result.end(), std::greater());
	Result.resize(3);

	std::cout << "result: " << std::accumulate(Result.begin(), Result.end(), 1, std::multiplies()) << "\n";
}
