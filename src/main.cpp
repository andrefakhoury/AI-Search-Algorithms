/*      ____  ____  ____
 *     / __ \/ __ \/ __ \
 *    / /  \/ /  \/ /  \ \
 *    \ \  / /\  / /\  / /
 *     \ \/ /\ \/ /\ \/ /
 *      \ \/  \ \/  \ \/
 *      /\ \  /\ \  /\ \
 *     / /\ \/ /\ \/ /\ \
 *    / /  \/ /  \/ /  \ \
 *   / /   / /\  / /\   \ \
 *   | |  / / /  \ \ \  | |
 *   \ \__\/ /    \/ /__/ /
 *    \_____/\____/ /____/
 *          \______/
 *
 * Artificial Intelligence - 2020.2 - ICMC USP
 * Implementation of mazes and search methods
 *
 * Developed by:
 *   Andre Luís Mendes Fakhoury
 *   David Cairuz da Silva
 *   Gustavo Vinicius Vieira Silva Soares
 *   Thiago Preischadt Pinheiro
 *
 * Important:
 *   If you are going to run visualize/benchmark, note that:
 *     - gnuplot must be installed;
 *     - 'visualize/vis.gp' and 'graphs/gen.gp' must have execution permission (chmod +x)
 *     - Maybe you'll have to change some #defines at 'include/Benchmark.hpp', according to the 'level' of the execution file
 *
 * Have fun! :)
 */

#include <iostream>
#include <fstream>
#include "Graph.hpp"
#include "Benchmark.hpp"

const int QTTMAZES = 10; // qtt of random matrices to generate
const int REPTIMES = 5; // qtt of times to repeat the search and improve benchmark precision

int main(int argc, char* argv[]) {
	// visualize path from each method on some random graph with fixed size and seed
	Graph g;
	g.generateRandom(Coordinate(50, 30), 132);
	visualizeSearches(g);

	// generate some random matrices
	for (int i = 1; i <= QTTMAZES; i++) {
		Graph newGraph;
		std::fstream dest("../samples/" + std::to_string(i) + ".in", std::ios::out);
		newGraph.generateRandom(i);
		newGraph.outputMatrix(dest);
		dest.close();
	}

	// run benchmark
	generateBenchmark(QTTMAZES, REPTIMES);

	return 0;
}
