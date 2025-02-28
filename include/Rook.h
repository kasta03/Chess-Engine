#pragma once
#include "Piece.h"

class Rook : public Piece
{
public:
    std::array<int, 4> possible_moves = {-8, -1, 1, 8};
};