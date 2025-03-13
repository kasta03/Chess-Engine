#include "BlackKnight.h"

bool BlackKnight::isWhite = false;
U64 BlackKnight::bitboard = 0b10000010 << 56;
std::vector<int> BlackKnight::linear_coordinates = {57, 62};
