#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct Vec2 {
	size_t X;
	size_t Y;

	size_t area(const Vec2 &Other) const {
		return (std::abs((int64_t)X - (int64_t)Other.X) + 1) * (std::abs((int64_t)Y - (int64_t)Other.Y) + 1);
	}
};

int main() {
	std::ifstream File("./input");
	std::stringstream FileContent;
	std::string Line;
	size_t Result = 0;

	FileContent << File.rdbuf();

	std::vector<Vec2 *> Points;

	while(std::getline(FileContent, Line, '\n')) {
		const size_t Comma = Line.find(',');

		Points.push_back(new Vec2{
			std::stoul(Line.substr(0, Comma).data()),
			std::stoul(Line.substr(Comma + 1).data()),
		});
	}

	for(size_t I = 0; I < Points.size(); ++I) {
		for(size_t J = I + 1; J < Points.size(); ++J) {
			Vec2 *LHS = Points[I];
			Vec2 *RHS = Points[J];
			const size_t Area = LHS->area(*RHS);

			if(Area > Result) {
				Result = Area;
			}
		}
	}

	std::cout << "result: " << Result << "\n";
}
