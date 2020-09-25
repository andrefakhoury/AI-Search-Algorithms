#include <random>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include "Graph.hpp"

Graph::Graph() : size(0, 0), startingPosition(-1, -1) { }

void Graph::readMatrix(std::istream &in) {
	in >> size.row >> size.col;
	assert(size.row > 0 && size.col > 0 && size.row <= MAXDIMENSION && size.col <= MAXDIMENSION);

	matrix.assign(size.row, std::vector<char>(size.col));

	for (int row = 0; row < size.row; row++) {
		for (int col = 0; col < size.col; col++) {
			in >> matrix[row][col];
			if (matrix[row][col] == STARTING) {
				startingPosition = {row, col};
			}
		}
	}
}

void Graph::generateRandom(unsigned long seed) {
	std::mt19937 rng(seed);
	size.row = (int) (rng() % MAXDIMENSION + 1);
	size.col = (int) (rng() % MAXDIMENSION + 1);
	generateRandom(size, seed);
}

void Graph::generateRandom(Coordinate fixedSize, unsigned long seed) {
	assert(fixedSize.valid(Coordinate(MAXDIMENSION + 1, MAXDIMENSION + 1)));

	this->size = fixedSize;
	std::mt19937 rng(seed);
	matrix.assign(size.row, std::vector<char>(size.col));

	// TODO
	const char* possibleElements = "*#-$";
	for (int row = 0; row < size.row; row++) {
		for (int col = 0; col < size.col; col++) {
			matrix[row][col] = possibleElements[rng() % 4];
		}
	}

}

void Graph::outputMatrix(std::ostream &out) {
	out << size.row << " " << size.col << "\n";
	for (int row = 0; row < size.row; row++) {
		for (int col = 0; col < size.col; col++) {
			out << matrix[row][col];
		}
		out << "\n";
	}
}

std::vector<Coordinate> Graph::depthFirstSearch() {
	assert(startingPosition.valid(size));

	std::vector<std::vector<bool>> visited(size.row, std::vector<bool>(size.col));
	std::vector<std::vector<Coordinate>> parent(size.row, std::vector<Coordinate>(size.col, Coordinate{-1, -1}));

	std::stack<Coordinate> st;
	st.push(startingPosition);
	visited[startingPosition.row][startingPosition.col] = true;

	Coordinate endingPosition(-1, -1);
	while(!st.empty()) {
		Coordinate cur = st.top();
		st.pop();

		if (matrix[cur.row][cur.col] == OBJECTIVE) {
			endingPosition = cur;
			break;
		}

		for (int delta = 0; delta < NDELTA; delta++) {
			int newRow = cur.row + deltaRow[delta];
			int newCol = cur.col + deltaCol[delta];
			Coordinate newCoord(newRow, newCol);
			if (newCoord.valid(size) && matrix[newRow][newCol] != OBSTACLE && !visited[newRow][newCol]) {
				visited[newRow][newCol] = true;
				parent[newRow][newCol] = cur;
				st.push(newCoord);
			}
		}
	}

	std::vector<Coordinate> path;
	Coordinate pos = endingPosition;
	while(pos != Coordinate(-1, -1)) {
			path.push_back(pos);
			pos = parent[pos.row][pos.col];
	}
	reverse(path.begin(), path.end());
	return path;
}

std::vector<Coordinate> Graph::breadthFirstSearch() {
	assert(startingPosition.valid(size));

	std::vector<std::vector<bool>> visited(size.row, std::vector<bool>(size.col));
	std::vector<std::vector<Coordinate>> parent(size.row, std::vector<Coordinate>(size.col, Coordinate{-1, -1}));

	std::queue<Coordinate> qu;
	qu.push(startingPosition);
	visited[startingPosition.row][startingPosition.col] = true;

	Coordinate endingPosition(-1, -1);
	while(!qu.empty()) {
		Coordinate cur = qu.front();
		qu.pop();

		if (matrix[cur.row][cur.col] == OBJECTIVE) {
			endingPosition = cur;
			break;
		}

		for (int delta = 0; delta < NDELTA; delta++) {
			int newRow = cur.row + deltaRow[delta];
			int newCol = cur.col + deltaCol[delta];
			Coordinate newCoord(newRow, newCol);
			if (newCoord.valid(size) && matrix[newRow][newCol] != OBSTACLE && !visited[newRow][newCol]) {
				visited[newRow][newCol] = true;
				parent[newRow][newCol] = cur;
				qu.push(newCoord);
			}
		}
	}

	std::vector<Coordinate> path;
	Coordinate pos = endingPosition;
	while(pos != Coordinate(-1, -1)) {
		path.push_back(pos);
		pos = parent[pos.row][pos.col];
	}
	reverse(path.begin(), path.end());
	return path;
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

void Graph::benchmark() {
	std::vector<std::vector<Coordinate> (Graph::*)()> vectorOfFunctions;
	vectorOfFunctions.push_back(&Graph::breadthFirstSearch);
	(this->*vectorOfFunctions[0])();
}

