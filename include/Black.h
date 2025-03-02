#pragma once
#include "Piece.h"

class Black: virtual public Piece
{
protected:
    const bool isWhite = false;
};