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
#include "Graph.hpp"
#include "Benchmark.hpp"

const int QTTMAZES = 2; // qtt of random matrices to generate
const int REPTIMES = 5; // qtt of times to repeat the search and improve benchmark precision

int main(int argc, char* argv[]) {
	Graph g;

//	std::fstream in("../samples/0.in", std::ios::in);
//	g.readMatrix(in);

	g.generateRandom(Coordinate(30, 30), 5);

	visualizeSearches(g);

//	auto x = g.bestFirstSearch();
//	for (auto c : x) {
//		std::cout << c.row << " " << c.row << "\n";
//	}

//
//
//	// generate some random matrices
//	for (int i = 1; i <= QTTMAZES; i++) {
//		Graph newGraph;
//		std::fstream dest("../samples/" + std::to_string(i) + ".in", std::ios::out);
//		newGraph.generateRandom(i);
//		newGraph.outputMatrix(dest);
//		dest.close();
//	}
//
//	generateBenchmark(QTTMAZES, REPTIMES);

	return 0;
}
