#pragma once
#include "Piece.h"

class Queen : public Piece
{
public:
    std::array<int, 8> possible_moves = {-9, -8, -7, -1, 1, 7, 8, 9};
};