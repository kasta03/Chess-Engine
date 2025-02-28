#pragma once
#include "WhitePawn.h"

bool isWhite = true;
U64 WhitePawn::white_pawns_mask = 0b11111111 << 8;

void WhitePawn::getPawnsPositions()
{
    for (int i = 0; i < 64; ++i)
    {
        white_pawn_positions[i] = WhitePawn::white_pawns_mask & (1ULL << i);
    }
}