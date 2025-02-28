#pragma once
#include "Pawn.h"

class BlackPawn : public Pawn
{
private:
    U64 black_pawns_position = 0b11111111ULL << 48;
    std::array<U64, 64> black_pawn_pre_moves;
    std::array<U64, 64> black_pawn_pre_attacks;
    std::array<U64, 64> black_pawn_positions;
    std::vector<std::pair<int, int>> black_pawn_moves;
    
public:
    void CalculateBlackPawnsPreMoves()
    {
        for (int i = 48; i > 7; --i)
        {
            black_pawn_pre_moves[i] = 1ULL << (i - 8);
            if (i / 8 == 6)
            {
                black_pawn_pre_moves[i] |= 1ULL << (i - 16);
            }
        }
    }
    void CalculateBlackPawnsPreAttacks()
    {
        for (int i = 48; i > 7; --i)
        {
            if (i % 8 != 0)
            {
                black_pawn_pre_attacks[i] |= 1ULL << (i - 9);
            }
            if (i % 8 != 7)
            {
                black_pawn_pre_attacks[i] |= 1ULL << (i - 7);
            }
        }
    }
    void getPawnPositions()
    {
        for (int i = 0; i < 64; ++i)
        {
            black_pawn_positions[i] = black_pawns_position & (1ULL << i);
        }
    }
    std::vector<std::pair<int, int>> CalculateBlackPawnMoves()
    {
        black_pawn_moves.clear();
        getPawnPositions();
        for (int i = 8; i < 56; ++i)
        {
            if (black_pawn_positions[i] != 0)
            {
                if (black_pawn_pre_moves[i] & all_pieces_mask)
                {
                    continue;
                }
                black_pawn_moves.push_back(std::make_pair(i, i - 8));
                if (i / 8 == 6 && (black_pawn_pre_moves[i] & all_pieces_mask) == 0)
                {
                    black_pawn_moves.push_back(std::make_pair(i, i - 16));
                }
                if (i % 8 != 0 && (black_pawn_pre_attacks[i] & white_pieces_mask) != 0)
                {
                    black_pawn_moves.push_back(std::make_pair(i, i - 9));
                }
                if (i % 8 != 7 && (black_pawn_pre_attacks[i] & white_pieces_mask) != 0)
                {
                    black_pawn_moves.push_back(std::make_pair(i, i - 7));
                }
            }
        }
        return black_pawn_moves;
    }
};
