#pragma once
#include "Pawn.h"

class WhitePawn
{
private:
    U64 white_pawns_position = 0b11111111 << 8;
    std::array<U64, 64> white_pawn_pre_moves;
    std::array<U64, 64> white_pawn_pre_attacks;
    std::array<U64, 64> white_pawn_positions;
    std::vector<std::pair<int, int>> white_pawn_moves;

public:
    void CalculateWhitePawnsPreMoves()
    {
        for (int i = 8; i < 56; ++i)
        {
            white_pawn_pre_moves[i] = 1ULL << (8 + i);
            if (i / 8 == 1)
            {
                white_pawn_pre_moves[i] |= 1ULL << (16 + i);
            }
        }
    }
    void CalculateWhitePawnsPreAttacks()
    {
        for (int i = 8; i < 56; ++i)
        {
            if (i % 8 != 0)
            {
                white_pawn_pre_attacks[i] |= 1ULL << (7 + i);
            }
            if (i % 8 != 7)
            {
                white_pawn_pre_attacks[i] |= 1ULL << (9 + i);
            }
        }
    }
    void getPawnPositions()
    {
        for (int i = 0; i < 64; ++i)
        {
            white_pawn_positions[i] = white_pawns_position & (1ULL << i);
        }
    }
    std::vector<std::pair<int, int>> CalculateWhitePawnMoves()
    {
        getPawnPositions();
        int steps = white_pawn_positions.size();
        int from; int to;
        for (int i = 0; i < steps; ++i)
        {
            
        }
    }
};