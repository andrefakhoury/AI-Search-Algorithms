#ifndef IA_PROJ1_COORDINATE_HPP
#define IA_PROJ1_COORDINATE_HPP

/**
 * Single coordinate <row, col>
 */
struct Coordinate {
	int row, col; // row and column

	/**
	 * Basic constructor with empty parameters, initialize each number with default integer constructors
	 */
	Coordinate();
	/**
	 * Basic constructor receiving specified row and column
	 * @param row Row of coordinate
	 * @param col Column of coordinate
	 */
	Coordinate(int row, int col);

	/**
	 * Check whether this coordinate is inbounded by a rectangle, with left lower index at [0, 0] and size bounds
	 * @param bounds Size of rectangle to bound
	 * @return whether this coordinate is in this rectangle
	 */
	bool valid(Coordinate const& bounds) const;

	/**
	 * Compare two coordinates
	 * @param rhs Right-hand side coordinate
	 * @return Whether the two coordinates are equal
	 */
	bool operator==(Coordinate const& rhs) const;

	/**
	 * Inequality comparator
	 * @param rhs Right-hand side coordinate
	 * @return Whether the two coordinates are not equal
	 */
	bool operator!=(Coordinate const& rhs) const;
};

/** Deltas for going down, up, left and right */
const int NDELTA = 4;
const int deltaRow[] = {1, -1, 0, 0};
const int deltaCol[] = {0, 0, -1, 1};

#endif //IA_PROJ1_COORDINATE_HPP
