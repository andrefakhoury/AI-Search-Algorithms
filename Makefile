all:
	g++ -o IA_Proj1 -I ./include/ src/Coordinate.cpp src/Benchmark.cpp src/Graph.cpp src/main.cpp -std=c++17

run:
	./IA_Proj1
