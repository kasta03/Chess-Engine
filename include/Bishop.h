#pragma once
#include "Piece.h"

class Bishop : public Piece
{

    public:
    std::array<int, 4> possible_moves = {-9, -7, 7, 9};
};