#ifndef IA_PROJ1_BENCHMARK_HPP
#define IA_PROJ1_BENCHMARK_HPP

#include <functional>
#include <string>
#include "Graph.hpp"
#include "Coordinate.hpp"

struct Method {
	std::string name;
	std::function<std::vector<Coordinate>()> fnSearch;
	Method(std::string const& name, std::function<std::vector<Coordinate>()> const& fnSearch);
};

void generateBenchmark(size_t qttMazes, size_t repTimes);
void visualizeSearches(Graph &graph);

#endif //IA_PROJ1_BENCHMARK_HPP
