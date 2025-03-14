#pragma once
#include "Piece.h"
#include "White.h"

class Black : virtual public Piece
{
protected:
    const bool isWhite = false;

public:
    Black(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
    static U64 squares_controlled;
};