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
 * Trabalho 1 de I.A. - 2020.2 - ICMC USP
 * Benchmarking de métodos de busca
 *
 *  4482145 - André Luís Mendes Fakhoury
 * XXXXXXXX - david
 * XXXXXXXX - gsoares
 * XXXXXXXX - preischadt
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include "Graph.hpp"
#include "Benchmark.hpp"

const int QTTMAZES = 10; // qtt of random matrices to generate
const int REPTIMES = 10; // qtt of times to repeat the search and improve benchmark precision

int main(int argc, char* argv[]) {
	// generate some random matrices

	for (int i = 1; i <= QTTMAZES; i++) {
		Graph newGraph;
		std::fstream dest("../samples/" + std::to_string(i) + ".in", std::ios::out);
		newGraph.generateRandom(i);
		newGraph.outputMatrix(dest);
		dest.close();
	}

	// Initialize benchmark methods
	Graph graph;
	std::vector<Method> methods;
	methods.emplace_back("Depth-first Search", [&]() {
		return graph.depthFirstSearch();
	});
	methods.emplace_back("Breadth-first Search", [&]() {
		return graph.breadthFirstSearch();
	});
	methods.emplace_back("Best-first Search", [&]() {
		return graph.bestFirstSearch();
	});
	methods.emplace_back("A*", [&]() {
		return graph.aStar();
	});
	methods.emplace_back("Hill Climbing", [&]() {
		return graph.hillClimbing();
	});

	for (int it = 0; it <= QTTMAZES; it++) {
		std::fstream in("../samples/" + std::to_string(it) + ".in", std::ios::in);

		std::cout << "Iteration " << it << ":\n";

		for (Method const& method : methods) {

			double elapsed = 0;
			for (int rep = 0; rep < REPTIMES; rep++) {
				graph.readMatrix(in);
				clock_t clockIni = clock();
				method.fnSearch();
				clock_t clockEnd = clock();
				elapsed += double(clockEnd - clockIni) / CLOCKS_PER_SEC;
			}
			elapsed /= REPTIMES;

			std::cout << std::fixed << std::setprecision(5) << method.name << ": " << elapsed << "\n";
		}

		std::cout << "\n-------------------\n";
		in.close();
	}

	return 0;
}
