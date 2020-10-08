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

// PATH to the files, from the view of executable. If the executable is at the same level, remove the '../'
#define PATH_GRAPHS "../graphs"
#define PATH_VISUALIZE "../visualize"

void generateBenchmark(size_t qttMazes, size_t repTimes);
void visualizeSearches(Graph &graph);

#endif //IA_PROJ1_BENCHMARK_HPP
