#pragma once
#include "Pawn.h"

class Bishop : public Pawn
{

    public:
    std::array<int, 4> possible_moves = {-9, -7, 7, 9};
};