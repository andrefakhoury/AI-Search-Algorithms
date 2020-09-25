#ifndef IA_PROJ1_COORDINATE_HPP
#define IA_PROJ1_COORDINATE_HPP

/**
 * Single coordinate <row, col>
 */
struct Coordinate {
	int row, col;
};

/**
 * Delta for going down, up, left and right
 */
const int deltaRow[] = {1, -1, 0, 0};
const int deltaCol[] = {0, 0, -1, 1};

#endif //IA_PROJ1_COORDINATE_HPP
