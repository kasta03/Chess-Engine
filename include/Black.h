#pragma once
#include "Piece.h"
#include "White.h"

class Black : virtual public Piece
{
protected:
    const bool isWhite = false;

public:
    static U64 squares_controlled;
};