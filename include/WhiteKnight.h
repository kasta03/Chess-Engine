#pragma once
#include "Knight.h"

class WhiteKnight : public Knight
{
private:
    std::vector<int> linear_coordinates {1, 6};
    std::array<U64, 64> white_knights_pre_attacks;
    std::array<std::vector<int>, 64> coordinates_white_knights_pre_attacks;
    // std::array<U64, 64> white_knights_masks;
    std::vector<std::pair<int, int>> white_knights_moves{};

public:
    static bool isWhite;
    static U64 white_knights_mask;
    
    void CalculateWhiteKnightsPreAttacks()
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
                        white_knights_pre_attacks[i] |= 1ULL << (to_square);
                        coordinates_white_knights_pre_attacks[i].push_back(to_square);
                    }
                }
            }
        }
    }
    std::vector<std::pair<int, int>> CalculateWhiteKnightsMoves()
    {
        white_knights_moves.clear();
        
        for (int current : linear_coordinates)
        {
            for (int to_coordinate : coordinates_white_knights_pre_attacks[current])
            {
                U64 target_mask = 1ULL << to_coordinate;
                if(!(target_mask & white_pieces_mask))
                {
                    white_knights_moves.push_back(std::make_pair(current, to_coordinate));
                }
            }
        }
        return white_knights_moves;
    }
    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 current_knight_mask, std::vector<int> linear_coordinates)
    {
        from_mask = 1ULL << pair.first;
        to_mask = 1ULL << pair.second;
        current_knight_mask ^= from_mask;
        current_knight_mask ^=to_mask;
        if (to_mask & black_pieces_mask)
        {
            MaskToCapture(to_mask, false);
        }

        int number;
        for(int i = 0; i < linear_coordinates.size(); ++i)
        {
            if(linear_coordinates.at(i) == pair.first)
            {
                linear_coordinates.at(i) += pair.second;
            }
        }
        return current_knight_mask;
    }
}