#include <fstream>
#include <iomanip>
#include "Benchmark.hpp"

Method::Method(const std::string &name, const std::function<std::vector<Coordinate>()> &fnSearch) :
	name(name), fnSearch(fnSearch) { }

/**
 * Initialize a vector with each search method on the graph send as reference
 * @param graph Graph to be used by each method
 * @return Vector with every method
 */
std::vector<Method> initializeMethods(Graph &graph) {
	std::vector<Method> methods;

	// declare each search function with a lambda function that captures the graph as reference
	methods.emplace_back("Depth-first", [&]() {
		return graph.depthFirstSearch();
	});
	methods.emplace_back("Breadth-first", [&]() {
		return graph.breadthFirstSearch();
	});
	methods.emplace_back("Best-first", [&]() {
		return graph.bestFirstSearch();
	});
	methods.emplace_back("A*", [&]() {
		return graph.aStar();
	});
	methods.emplace_back("Hill-Climbing", [&]() {
		return graph.hillClimbing();
	});
	return methods;
}

void generateBenchmark(const size_t qttMazes, const size_t repTimes) {
	// Initialize benchmark methods
	Graph graph;
	std::vector<Method> methods = initializeMethods(graph);

	// iterate each maze
	for (size_t it = 0; it <= qttMazes; it++) {
		std::fstream in("../samples/" + std::to_string(it) + ".in", std::ios::in);
		std::fstream gnuplotData("../graphs/data/m" + std::to_string(it) + ".dat", std::ios::out);
		gnuplotData << std::fixed << std::setprecision(5);

		double maxTime = 0;

		// prints the number of current maze that is being benchmarked
		std::cout << "Maze " << it << "...\n";

		// iterate each method
		for (int idm = 0; idm < (int) methods.size(); idm++) {
			Method const& method = methods[idm];
			double elapsed = 0;
			// iterate the same method repTimes
			for (size_t rep = 0; rep < repTimes; rep++) {
				graph.readMatrix(in);
				clock_t clockIni = clock();
				method.fnSearch();
				clock_t clockEnd = clock();
				elapsed += double(clockEnd - clockIni) / CLOCKS_PER_SEC;
			}
			elapsed /= repTimes;
			maxTime = std::max(maxTime, elapsed);

			gnuplotData << idm << " \"" << method.name << "\" " << elapsed << "\n";
		}

		in.close();
		gnuplotData.close();

		// execute gnuplot for this data
		char command[256];
		sprintf(command, PATH_GRAPHS "/gen.gp %ld %.3lf", it, maxTime * 1.25);
		system(command);
	}
}

void visualizeSearches(Graph &graph) {
	// Initialize benchmark methods
	std::vector<Method> methods = initializeMethods(graph);

	// useless function to print empty maze
	methods.emplace_back("Empty", [&]() {
		return std::vector<Coordinate>{};
	});

	// define each color
	const int COLOR_PATH = 2;
	const int COLOR_START = 1;
	const int COLOR_OBSTACLE = 0;
	const int COLOR_NONE = 5;

	// execute each method
	for (const Method method : methods) {
		std::fstream gnuplotData("../visualize/data/" + method.name + ".dat", std::ios::out);

		std::vector<Coordinate> path = method.fnSearch();
		std::vector<std::vector<int>> maze(graph.size.row, std::vector<int>(graph.size.col, COLOR_NONE));

		std::cerr << "Size of path using " << method.name << ": " << path.size() << "\n";

		// set color for path
		for (const Coordinate coord : path) {
			maze[coord.row][coord.col] = COLOR_PATH;
		}

		// set color for obstacles and starting/end position
		for (int i = 0; i < graph.size.row; i++) {
			for (int j = 0; j < graph.size.col; j++) {
				if (graph.matrix[i][j] == Graph::Position::OBJECTIVE || graph.matrix[i][j] == Graph::Position::STARTING)
					maze[i][j] = COLOR_START;
				else if (graph.matrix[i][j] == Graph::Position::OBSTACLE)
					maze[i][j] = COLOR_OBSTACLE;

				// print to gnuplot data
				gnuplotData << maze[i][j] << " ";
			}
			gnuplotData << "\n";
		}
		gnuplotData.close();

		// execute gnuplot for this data
		char command[256];
		sprintf(command, PATH_VISUALIZE "/vis.gp \"%s\"", method.name.c_str());
		system(command);
	}
}