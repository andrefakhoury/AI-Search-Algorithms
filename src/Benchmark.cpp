#include <fstream>
#include <iomanip>
#include "Benchmark.hpp"

Method::Method(const std::string &name, const std::function<std::vector<Coordinate>()> &fnSearch) : name(name), fnSearch(fnSearch) { }

std::vector<Method> initializeMethods(Graph &graph) {
	std::vector<Method> methods;
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

	for (size_t it = 0; it <= qttMazes; it++) {
		std::fstream in("../samples/" + std::to_string(it) + ".in", std::ios::in);
		std::fstream gnuplotData("../graphs/data/m" + std::to_string(it) + ".dat", std::ios::out);
		gnuplotData << std::fixed << std::setprecision(5);

		double maxTime = 0;

		std::cout << "Maze " << it << "...\n";

		for (int idm = 0; idm < (int) methods.size(); idm++) {
			Method const& method = methods[idm];
			double elapsed = 0;
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
		sprintf(command, "../graphs/gen.gp %ld %.3lf", it, maxTime * 1.1);
		system(command);
	}
}


void visualizeSearches(Graph &graph) {
	// Initialize benchmark methods
	std::vector<Method> methods = initializeMethods(graph);

	// define each color
	const int COLOR_PATH = 2;
	const int COLOR_START = 1;
	const int COLOR_OBSTACLE = 5;

	// execute each method
	for (const Method method : methods) {
		std::fstream gnuplotData("../visualize/data/" + method.name + ".dat", std::ios::out);

		std::vector<Coordinate> path = method.fnSearch();
		std::vector<std::vector<int>> maze(graph.size.row, std::vector<int>(graph.size.col));

		std::cout << method.name << ": " << path.size() << "\n";

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
		sprintf(command, "../visualize/vis.gp \"%s\"", method.name.c_str());
		system(command);
		system("sleep 1");
	}
}