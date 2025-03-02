#pragma once
#include "BlackQueen.h"

bool BlackQueen::isBlack = false;
U64 BlackQueen::bitboard = 00001000 << 56;
std::vector<int> BlackQueen::linear_coordinates = {59};