#pragma once
#include "Pawn.h"

class WhitePawn : public Pawn
{
public:
    static std::array<U64, 64> white_pawn_pre_moves;
    std::array<U64, 64> white_pawn_pre_attacks;
    std::array<U64, 64> white_pawn_positions;
    std::vector<std::pair<int, int>> white_pawn_moves;

public:
    static bool isWhite;
    static U64 white_pawns_mask;
    
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
    void getPawnsPositions();
    
    std::vector<std::pair<int, int>> CalculateWhitePawnsMoves()
    {
        white_pawn_moves.clear();
        getPawnsPositions();
        for (int i = 0; i < 56; ++i)
        {
            if (white_pawn_positions[i] != 0)
            {
                if (white_pawn_pre_moves[i] & all_pieces_mask)
                {
                    continue;
                }
                white_pawn_moves.push_back(std::make_pair(i, i + 8));
                if (i / 8 == 1 && (white_pawn_pre_moves[i] & all_pieces_mask) == 0)
                {
                    white_pawn_moves.push_back(std::make_pair(i, i + 16));
                }
                if (i % 8 != 0 && (white_pawn_pre_attacks[i] & black_pieces_mask) != 0)
                {
                    white_pawn_moves.push_back(std::make_pair(i, i + 7));
                }
                if (i % 8 != 7 && (white_pawn_pre_attacks[i] & black_pieces_mask) != 0)
                {
                    white_pawn_moves.push_back(std::make_pair(i, i + 9));
                }
            }
        }
        return white_pawn_moves;
    }
};