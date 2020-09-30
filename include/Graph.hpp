#ifndef IA_PROJ1_GRAPH_HPP
#define IA_PROJ1_GRAPH_HPP

#include "Coordinate.hpp"
#include <vector>
#include <iostream>

/**
 * - Read matrix
 * 	- Generate random matrix
 *
 * 	- Algorithms
 * 	  - Depth-First Search (DFS)
 * 	  - Breadth-First Search (BFS)
 * 	  - Best-First Search
 * 	  - A*
 * 	  - Hill Climbing
 */

const int MAXDIMENSION = 1000;

class Graph {
public:
	enum Position {
		VALID = '*',
		STARTING = '#',
		OBSTACLE = '-',
		OBJECTIVE = '$',
		SPECIAL = '!'
	};
	Coordinate size{};
	Coordinate startingPosition{};
	std::vector<std::vector<char>> matrix;

	Graph();
	void readMatrix(std::istream& in);
	void generateRandom(unsigned long seed);
	void generateRandom(Coordinate fixedSize, unsigned long seed);
	void outputMatrix(std::ostream& out);
	bool checkValid();
	std::vector<Coordinate> depthFirstSearch();
	std::vector<Coordinate> breadthFirstSearch();
	std::vector<Coordinate> bestFirstSearch();
	std::vector<Coordinate> aStar();
	std::vector<Coordinate> hillClimbing();
};

#endif //IA_PROJ1_GRAPH_HPP