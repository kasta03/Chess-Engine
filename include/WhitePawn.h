#pragma once
#include "Pawn.h"

class WhitePawn
{
    private:
    U64 white_pawns_position = 0b11111111 << 8;
    std::array<U64, 64> white_pawn_pre_moves{1};
    
    public:
    void CalculateWhitePawnsPreMoves()
    {
        for (int i = 8; i < 64; ++i)
        {
            white_pawn_pre_moves[i] <<= 8; 
            if (i / 8 == 1)
            {
                white_pawn_pre_moves[i] = white_pawn_pre_moves[i] & white_pawn_pre_moves[i] << 8; 
            }
        }
    }
};