#pragma once
#include "BlackBishop.h"

bool BlackBishop::isWhite = false;
U64 BlackBishop::bitboard = 0b00100100 << 56;
std::vector<int> BlackBishop::linear_coordinates = {58, 61};