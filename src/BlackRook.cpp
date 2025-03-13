#include "BlackRook.h"

bool BlackRook::isBlack = false;
U64 BlackRook::bitboard = 0b10000001 << 56;
std::vector<int> BlackRook::linear_coordinates = {56, 63};
