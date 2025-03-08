#pragma once
#include "King.h"
#include "White.h"

class WhiteKing : public King, public White
{
public:
    void CalculateWhiteKingPreAttacks()
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
                    if ((diff_file == 1 && diff_rank == 1) || (diff_file == 1 && diff_rank == 0) || (diff_file == 0 && diff_rank == 1))
                    {
                        pre_attacks_coordinates[i].push_back(to_square);
                    }
                }
            }
        }
    }
    std::vector<std::pair<int, int>> CalculateWhiteKingMoves()
    {
        moves_vector.clear();
        
        for (int from_square : linear_coordinates)
        {
            for (int to_square : pre_attacks_coordinates[from_square])
            {
                U64 target_mask = 1ULL << to_square;
                if(!(target_mask & white_pieces_mask) && !(target_mask & Black::squares_controlled))
                {
                    moves_vector.push_back(std::make_pair(from_square, to_square));
                    squares_controlled |= target_mask;
                }
            }
        }
        return moves_vector;
    }
    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 from_square_king_mask, std::vector<int>& linear_coordinates)
    {
        U64 from_mask = 1ULL << move_to_execute.first;
        U64 to_mask = 1ULL << move_to_execute.second;
        from_square_king_mask ^= from_mask;
        from_square_king_mask ^= to_mask;
        if (to_mask & black_pieces_mask)
        {
            MaskToCapture(to_mask, false);
        }

        for(int i = 0; i < linear_coordinates.size(); ++i)
        {
            if(linear_coordinates.at(i) == move_to_execute.first)
            {
                linear_coordinates.at(i) = move_to_execute.second;
            }
        }
        return from_square_king_mask;
    }
};





