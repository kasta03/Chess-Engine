#include "BlackPawn.h"

bool BlackPawn::isWhite = false;
U64 BlackPawn::bitboard = 0b11111111 << 48;
std::vector<int> BlackPawn::linear_coordinates = {48, 49, 50, 51, 52, 53, 54, 55};
