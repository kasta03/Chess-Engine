#pragma once
#include "Piece.h"

class Bishop : virtual public Piece
{
protected:
    std::array<int, 4> possible_moves = {-9, -7, 7, 9};
public:
    Bishop(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
};