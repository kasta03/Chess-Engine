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
    static U64 squares_controlled;
};