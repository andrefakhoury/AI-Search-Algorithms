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

void generateBenchmark(const size_t qttMazes, const size_t repTimes);

#endif //IA_PROJ1_BENCHMARK_HPP
