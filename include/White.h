#pragma once
#include "Piece.h"

class White: virtual public Piece
{
protected:
    const bool isWhite = true;
    U64 squares_controlled = 0;
};