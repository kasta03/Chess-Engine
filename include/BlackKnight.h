#pragma once
#include "Knight.h"

class BlackKnight : public Knight
{
public:
    BlackKnight(U64 bitboard = U64(0b01000010) << 56, std::vector<int> linear_coordinates = {57, 62}) : Piece(bitboard, linear_coordinates)
    {
        CalculateBlackKnightsPreAttacks();
    }
    void CalculateBlackKnightsPreAttacks()
    {
        for (int i = 0; i < 64; ++i)
        {
            int from_rank = i / 8;
            int from_file = i % 8;

            for (int j = 0; j < 8; ++j)
            {
                int to_square = i + possible_moves[j];
                if (to_square >= 0 && to_square < 64)
                {
                    int to_rank = to_square / 8;
                    int to_file = to_square % 8;
                    int diff_rank = abs(from_rank - to_rank);
                    int diff_file = abs(from_file - to_file);
                    if (diff_file + diff_rank == 3 && diff_file > 0 && diff_rank > 0)
                    {
                        pre_attacks_coordinates[i].push_back(to_square);
                    }
                }
            }
        }
    }

    std::vector<std::pair<int, int>> CalculateBlackKnightsMoves()
    {
        moves_vector.clear();

        for (int from_square : linear_coordinates)
        {
            for (int to_square : pre_attacks_coordinates[from_square])
            {
                U64 target_mask = 1ULL << to_square;
                if (!(target_mask & black_bitboard))
                {
                    moves_vector.push_back(std::make_pair(from_square, to_square));
                }
            }
        }
        return moves_vector;
    }

    // U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 current_knight_mask, std::vector<int> &linear_coordinates)
    // {
    //     U64 from_mask = 1ULL << move_to_execute.first;
    //     U64 to_mask = 1ULL << move_to_execute.second;
    //     current_knight_mask ^= from_mask;
    //     current_knight_mask ^= to_mask;
    //     if (to_mask & white_bitboard)
    //     {
    //         MaskToCapture(to_mask, true);
    //     }

    //     for (int i = 0; i < linear_coordinates.size(); ++i)
    //     {
    //         if (linear_coordinates.at(i) == move_to_execute.first)
    //         {
    //             linear_coordinates.at(i) = move_to_execute.second;
    //         }
    //     }

    //     return current_knight_mask;
    // }
};
