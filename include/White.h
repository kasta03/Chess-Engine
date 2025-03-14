#pragma once
#include "Piece.h"
#include "Black.h"

class White: virtual public Piece
{
private:
    static std::array<U64, 6> bitboards;
    
protected:
    const bool isWhite = true;

public:
    White(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
    static U64 squares_controlled;
};