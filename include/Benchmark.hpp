#ifndef IA_PROJ1_BENCHMARK_HPP
#define IA_PROJ1_BENCHMARK_HPP

#include <functional>
#include <string>
#include "Graph.hpp"
#include "Coordinate.hpp"

/**
 * Struct for a method, containing the name and the function that realizes the search
 */
struct Method {
	std::string name;
	std::function<std::vector<Coordinate>()> fnSearch;
	/**
	 * Constructor for a method
	 * @param name Name of the method
	 * @param fnSearch Search function of the method
	 */
	Method(std::string const& name, std::function<std::vector<Coordinate>()> const& fnSearch);
};

// PATH to the files, from the view of executable. If the executable is at the same level, remove the '../'
#define PATH_GRAPHS "../graphs"
#define PATH_VISUALIZE "../visualize"

/**
 * Generate a benchmark, plotting the result on a gnuplot bar graph
 * @param qttMazes Quantity of mazes + 1, enumerated by [0..qttMazes] (0 is the sample maze)
 * @param repTimes Quantity of iterations to realize the time testing. The mean time is considered.
 */
void generateBenchmark(size_t qttMazes, size_t repTimes);

/**
 * Generate visualizations, plotting the maze as a matrix by gnuplot
 * @param graph The graph to realize the searches
 */
void visualizeSearches(Graph &graph);

#endif //IA_PROJ1_BENCHMARK_HPP
