#pragma once
#include "Piece.h"

class Queen : virtual public Piece
{
protected:
    std::array<int, 8> possible_moves = {-9, -8, -7, -1, 1, 7, 8, 9};
public:
    Queen(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
};