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

/** Class Graph contains the maze positions and all search algorithms
 * 
 * To represent the maze, an adjacency matrix is used in the form
 * of a 2D vector.
 */

class Graph {
public:
	/** Position classifies tiles in the maze. */
	enum Position {
		VALID = '*',
		STARTING = '#',
		OBSTACLE = '-',
		OBJECTIVE = '$',
		SPECIAL = '!'
	};

	Coordinate size{}; // maze size
	Coordinate startingPosition{}; // starting position in the maze
	std::vector<std::vector<char>> matrix; // actual maze

	Graph();
	
	/** readMatrix is used to read the maze from an input stream.
	 * 
	 * The usage of an istream provides the possibility of using a
	 * specific output stream (for example a file stream), aswell as
	 * stdin.
	 * 
	 * @param in input stream to be read from
	 */ 
	void readMatrix(std::istream& in);

	/** generateRandom creates a random maze.

	 * @param seed seed to be used in RNG
	 */ 
	void generateRandom(unsigned long seed);

	/** generateRandom creates a random maze.
	 * 
	 * @param fixedSize size of the maze
	 * @param seed seed to be used in RNG
	 */ 
	void generateRandom(Coordinate fixedSize, unsigned long seed);

	/** outputMatrix prints the maze to a specific output stream
	 * 
	 * The usage of an ostream provides the possibility of using a
	 * specific output stream (for example a file stream), aswell as 
	 * stdout.
	 * 
	 * @param out output stream to be used
	 */ 
	void outputMatrix(std::ostream& out);

	/** checkValid checks whether the graph is valid.
	 * 
	 * Validity here is expressed by the maze being solvable.
	 * 
	 * @returns feasibility of the maze
	 */ 
	bool checkValid();

	/** depthFirstSearch runs a DFS search on the maze
	 *  
	 * @returns path from starting to ending position
	 */
	std::vector<Coordinate> depthFirstSearch();

	/** breadthFirstSearch runs a BFS search on the maze
	 *  
	 * @returns path from starting to ending position
	 */
	std::vector<Coordinate> breadthFirstSearch();

	/** bestFirstSearch runs the Dijkstra algorithm on the maze
	 *  
	 * @returns path from starting to ending position
	 */
	std::vector<Coordinate> bestFirstSearch();

	/** aStar runs the A* algorithm on the maze
	 *  
	 * @returns path from starting to ending position
	 */
	std::vector<Coordinate> aStar();

	/** hillClimbing runs the Hill Climbing search on the maze
	 *  
	 * @returns path from starting to ending position
	 */
	std::vector<Coordinate> hillClimbing();
};

#endif //IA_PROJ1_GRAPH_HPP