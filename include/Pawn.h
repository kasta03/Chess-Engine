#pragma once
#include "Piece.h"

class Pawn : virtual public Piece
{
public:
    Pawn(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
    // Pawn(U64 bitboard, std::vector<int> linear_coordinates);
};