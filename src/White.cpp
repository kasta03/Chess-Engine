#pragma once
#include "White.h"

U64 White::squares_controlled = 0;
std::array<U64, 6> bitboards = WhitePawn::bitboard