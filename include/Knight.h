#pragma once
#include "Piece.h"

class Knight : virtual public Piece
{
protected:    
    std::array<int, 8> possible_moves = {6, 15, 17, 10, -6, -15, -17, -10};
public:
    Knight(U64 bitboard = 0, std::vector<int> linear_coordinates = {}) : Piece(bitboard, linear_coordinates) {}
};