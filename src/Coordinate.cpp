#include "Coordinate.hpp"

Coordinate::Coordinate() : row(), col() { }

Coordinate::Coordinate(int row, int col) : row(row), col(col) { }

bool Coordinate::valid(const Coordinate &bounds) const {
	// it must be inside the rectangle delimited by bounds
	return row >= 0 && col >= 0 && row < bounds.row && col < bounds.col;
}

bool Coordinate::operator==(const Coordinate &rhs) const {
	return row == rhs.row && col == rhs.col;
}

bool Coordinate::operator!=(const Coordinate &rhs) const {
	return row != rhs.row || col != rhs.col;
}