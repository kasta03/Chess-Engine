#pragma once
#include "Piece.h"

class Rook : virtual public Piece
{
protected:
    std::array<int, 4> possible_moves = {-8, -1, 1, 8};
};