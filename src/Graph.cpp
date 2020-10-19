#include <random>
#include <cassert>
#include <stack>
#include <queue>
#include <algorithm>
#include "Graph.hpp"

Graph::Graph() : size(0, 0), startingPosition(-1, -1) { }

void Graph::readMatrix(std::istream &in) {
	// read dimensions
	in >> size.row >> size.col;

	// checks if the dimensions are valid
	assert(size.row > 0 && size.col > 0 && size.row <= MAXDIMENSION && size.col <= MAXDIMENSION);

	// creates the matrix
	matrix.assign(size.row, std::vector<char>(size.col));

	// fill matrix
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
	// random seed
	std::mt19937 rng(seed);

	// generate size and call the other generateRandom function
	size.row = (int) (rng() % (MAXDIMENSION - 1) + 2);
	size.col = (int) (rng() % (MAXDIMENSION - 1) + 2);
	generateRandom(size, seed);
}

void Graph::generateRandom(Coordinate fixedSize, unsigned long seed) {
	// assert the size is valid
	assert(fixedSize.row >= 2 && fixedSize.col >= 2);
	assert(fixedSize.valid(Coordinate(MAXDIMENSION + 1, MAXDIMENSION + 1)));

	// create matrix
	this->size = fixedSize;
	std::mt19937 rng(seed);
	matrix.assign(size.row, std::vector<char>(size.col, SPECIAL));

	// generate starting and ending position
	Coordinate starting(rng()%size.row, rng()%size.col);
	Coordinate ending = starting;
	while(ending == starting) {
		ending = Coordinate(rng()%size.row, rng()%size.col);
	}
	matrix[starting.row][starting.col] = STARTING;
	matrix[ending.row][ending.col] = OBJECTIVE;
	startingPosition = starting;

	// iterate until matrix is valid. Increase the probability of valid positions instead of obstacles on each iteration
	for (int qttValid = 1, qttObstacle = 1; !checkValid(); qttValid += 2, qttObstacle++) {
		qttValid = std::min(qttValid, MAXDIMENSION * MAXDIMENSION);
		qttObstacle = std::min(qttObstacle, (MAXDIMENSION * MAXDIMENSION) / 2);

		// possible elements to be on maze, according to its probability
		std::string possibleElements = std::string(qttValid, VALID) + std::string(qttObstacle, OBSTACLE);
		for (int row = 0; row < size.row; row++) {
			for (int col = 0; col < size.col; col++) if (matrix[row][col] != STARTING && matrix[row][col] != OBJECTIVE) {
				matrix[row][col] = possibleElements[rng() % possibleElements.size()];
			}
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

bool Graph::checkValid() {
	int countStarting = 0; // number of starting positions
	int countObjective = 0; // number of ending positions

	// check quantity of starting, ending and special
	for (int row = 0; row < size.row; row++) {
		for (int col = 0; col < size.col; col++) {
			countStarting += matrix[row][col] == STARTING;
			countObjective += matrix[row][col] == OBJECTIVE;
			if (matrix[row][col] == SPECIAL) {
				return false;
			}
		}
	}

	// it can be only one starting and one objective position
	if (countStarting != 1 || countObjective != 1) {
		return false;
	}

	// uses DFS to check if exists a valid path
	if (depthFirstSearch().empty()) {
		return false;
	}

	return true;
}

std::vector<Coordinate> Graph::depthFirstSearch() {
	assert(startingPosition.valid(size));

	// vector for visited coordinates
	std::vector<std::vector<bool>> visited(size.row, std::vector<bool>(size.col));

	// parent of each vertex (who called each vertex)
	std::vector<std::vector<Coordinate>> parent(size.row, std::vector<Coordinate>(size.col, Coordinate{-1, -1}));

	// default dfs function
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

	// recover path found
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

	// default BFS function
	std::queue<Coordinate> qu;
	qu.push(startingPosition);
	visited[startingPosition.row][startingPosition.col] = true;

	Coordinate endingPosition(-1, -1);
	while(!qu.empty()) {
		Coordinate cur = qu.front();
		qu.pop();

		// check if objective is found
		if (matrix[cur.row][cur.col] == OBJECTIVE) {
			endingPosition = cur;
			break;
		}

		// go to each neighbour
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

	// recover path
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
    assert(startingPosition.valid(size));

    // find ending position to apply heuristic
    Coordinate endingPosition;
    for (int i = 0; i < size.row; i++) {
        for (int j = 0; j < size.col; j++) {
            if (matrix[i][j] == OBJECTIVE) {
                endingPosition.row = i;
                endingPosition.col = j;
            }
        }
    }

    std::vector<std::vector<Coordinate>> parent(size.row, std::vector<Coordinate>(size.col, {-1, -1}));
    std::vector<std::vector<char>> visited(size.row, std::vector<char>(size.col, false));

    // pair of distance to objective and current coordinate
    using cost_coord = std::pair<int, Coordinate>;
    auto comp = [](cost_coord a, cost_coord b) {
    	return a.first > b.first;
    };
    std::priority_queue<cost_coord, std::vector<cost_coord>, decltype(comp)> pq(comp);

    pq.push({0, startingPosition});
    visited[startingPosition.row][startingPosition.col] = true;

    // loop until there is some possible vertex
    while(!pq.empty()) {
		Coordinate cur = pq.top().second;
        pq.pop();

        // objective found
        if (matrix[cur.row][cur.col] == OBJECTIVE) {
            break;
        }

        // reach each neighbour
        for (int delta = 0; delta < NDELTA; delta++) {
            int newRow = cur.row + deltaRow[delta];
            int newCol = cur.col + deltaCol[delta];
            Coordinate nxt(newRow, newCol);

            if (nxt.valid(size) && matrix[newRow][newCol] != OBSTACLE && !visited[newRow][newCol]) {
                visited[newRow][newCol] = true;
                parent[newRow][newCol] = cur;

                // Manhattan distance
                int c_nxt = std::abs(nxt.row - endingPosition.row) + std::abs(nxt.col - endingPosition.col);
                pq.push({c_nxt, nxt});
            }
        }
    }

    // recover path
    std::vector<Coordinate> path;
    Coordinate pos = endingPosition;
    while(pos != Coordinate(-1, -1)) {
        path.push_back(pos);
        pos = parent[pos.row][pos.col];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Coordinate> Graph::aStar() {
    assert(startingPosition.valid(size));

    // get ending position to apply heuristics
    Coordinate endingPosition;
    for (int i = 0; i < size.row; i++) {
        for (int j = 0; j < size.col; j++) {
            if (matrix[i][j] == OBJECTIVE) {
                endingPosition.row = i;
                endingPosition.col = j;
            }
        }
    }

    std::vector<std::vector<Coordinate>> parent(size.row, std::vector<Coordinate>(size.col, {-1, -1}));

    // distance and cost vectors
    int max_dist = size.row * size.col + 1;
    std::vector<std::vector<int>> dist(size.row, std::vector<int>(size.col, max_dist));
    std::vector<std::vector<int>> cost(size.row, std::vector<int>(size.col, max_dist));

    // comparison
    using cost_coord = std::pair<int, Coordinate>;
    auto comp = [](cost_coord a, cost_coord b) {
    	return a.first > b.first;
    };
    std::priority_queue<cost_coord, std::vector<cost_coord>, decltype(comp)> pq(comp);

    // add starting vertex to queue
    pq.push({0, startingPosition});
    dist[startingPosition.row][startingPosition.col] = 0;
    cost[startingPosition.row][startingPosition.col] = 0;

    while(!pq.empty()) {
        auto [c, cur] = pq.top(); // get best possible vertex
        pq.pop();

        if (c != cost[cur.row][cur.col]) {
            continue;
        }
        if (matrix[cur.row][cur.col] == OBJECTIVE) {
            break;
        }

        // reach each neighbour
        for (int delta = 0; delta < NDELTA; delta++) {
            int newRow = cur.row + deltaRow[delta];
            int newCol = cur.col + deltaCol[delta];
            Coordinate nxt(newRow, newCol);

            // relax the edge
            if (nxt.valid(size) && matrix[newRow][newCol] != OBSTACLE && dist[newRow][newCol] > dist[cur.row][cur.col] + 1) {
                dist[newRow][newCol] = dist[cur.row][cur.col] + 1;
                parent[newRow][newCol] = cur;

                int c_nxt = std::abs(nxt.row - endingPosition.row) + std::abs(nxt.col - endingPosition.col);
                cost[newRow][newCol] = dist[newRow][newCol] + c_nxt;
                pq.push({cost[newRow][newCol], nxt});
            }
        }
    }

    // recover path
    std::vector<Coordinate> path;
    Coordinate pos = endingPosition;
    while(pos != Coordinate(-1, -1)) {
        path.push_back(pos);
        pos = parent[pos.row][pos.col];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<Coordinate> Graph::hillClimbing() {
	assert(startingPosition.valid(size));

	std::vector<std::vector<bool>> visited(size.row, std::vector<bool>(size.col));
	std::vector<std::vector<Coordinate>> parent(size.row, std::vector<Coordinate>(size.col, Coordinate{-1, -1}));

	// add starting vertex to stack
	std::stack<Coordinate> st;
	st.push(startingPosition);
	visited[startingPosition.row][startingPosition.col] = true;

	Coordinate endingPosition;

	// get ending position to apply heuristic
    for (int i = 0; i < size.row; i++) {
        for (int j = 0; j < size.col; j++) {
            if (matrix[i][j] == OBJECTIVE) {
                endingPosition.row = i;
                endingPosition.col = j;
            }
        }
    }
	
	std::vector<Coordinate> path;

	while(!st.empty()) {
		Coordinate cur = st.top();
		st.pop();

		path.push_back(cur);

		if (cur == endingPosition) {
			break;
		}

		std::vector<Coordinate> neighbours;

		// try each neighbour
		for (int delta = 0; delta < NDELTA; delta++) {
			int newRow = cur.row + deltaRow[delta];
			int newCol = cur.col + deltaCol[delta];
			Coordinate newCoord(newRow, newCol);

			if (newCoord.valid(size) && matrix[newRow][newCol] != OBSTACLE && !visited[newRow][newCol]) {
				neighbours.push_back(newCoord);
			}

		}

		// see who's best
		auto distToEnding = [&](Coordinate& a) {
			int da = abs(a.row - endingPosition.row) + abs(a.col - endingPosition.col);
			return da;
		};

		Coordinate bestNeighbor(-1, -1);

		for(Coordinate n : neighbours) {
			if (bestNeighbor == Coordinate(-1, -1) or distToEnding(bestNeighbor) > distToEnding(n)) {
				bestNeighbor = n;
			}
		}

		// go to best next candidate
		if (distToEnding(bestNeighbor) <= distToEnding(cur)) {
			visited[bestNeighbor.row][bestNeighbor.col] = true;
			parent[bestNeighbor.row][bestNeighbor.col] = cur;
			st.push(bestNeighbor);
		}
	}

	return path;
}

