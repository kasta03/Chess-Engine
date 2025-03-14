#pragma once
#include "Piece.h"

class Rook : virtual public Piece
{
protected:
    std::array<int, 4> possible_moves = {-8, -1, 1, 8};
public:
    Rook(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
};