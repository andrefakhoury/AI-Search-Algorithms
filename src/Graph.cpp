#include <random>
#include <cassert>
#include "Graph.hpp"

void Graph::readMatrix(std::istream &in) {
	in >> nRows >> nCols;
	assert(nRows > 0 && nCols > 0 && nRows <= MAXDIMENSION && nCols <= MAXDIMENSION);

	matrix.assign(nRows, std::vector<char>(nCols));

	for (int row = 0; row < nRows; row++) {
		for (int col = 0; col < nCols; col++) {
			in >> matrix[row][col];
		}
	}
}

void Graph::generateRandom(unsigned long seed) {
	std::mt19937 rng(seed);

	nRows = (int) rng() % MAXDIMENSION + 1;
	nCols = (int) rng() % MAXDIMENSION + 1;

	matrix.assign(nRows, std::vector<char>(nCols));

	// TODO
	const char* possibleElements = "*#-$";
	for (int row = 0; row < nRows; row++) {
		for (int col = 0; col < nCols; col++) {
			matrix[row][col] = possibleElements[rng() % 4];
		}
	}
}

void Graph::outputMatrix(std::ostream &out) {
	for (int row = 0; row < nRows; row++) {
		for (int col = 0; col < nCols; col++) {
			out << matrix[row][col];
		}
		out << "\n";
	}
}

std::vector<Coordinate> Graph::depthFirstSearch() {
	return std::vector<Coordinate>();
}

std::vector<Coordinate> Graph::breadthFirstSearch() {
	return std::vector<Coordinate>();
}

std::vector<Coordinate> Graph::bestFirstSearch() {
	return std::vector<Coordinate>();
}

std::vector<Coordinate> Graph::aStar() {
	return std::vector<Coordinate>();
}

std::vector<Coordinate> Graph::hillClimbing() {
	return std::vector<Coordinate>();
}
