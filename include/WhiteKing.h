#pragma once
#include "King.h"
#include "White.h"

class WhiteKing : public King, public White
{
private:
    std::vector<int> linear_coordinates {4};
    std::array<U64, 64> white_king_pre_attacks;
    std::array<std::vector<int>, 64> coordinates_white_king_pre_attacks;
    std::vector<std::pair<int, int>> white_king_moves{};

public:
    static bool isWhite;
    static U64 white_king_mask;
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
                        white_king_pre_attacks[i] |= 1ULL << (to_square);
                        coordinates_white_king_pre_attacks[i].push_back(to_square);
                    }
                }
            }
        }
    }
    std::vector<std::pair<int, int>> CalculateWhiteKingMoves()
    {
        white_king_moves.clear();
        
        for (int from_square : linear_coordinates)
        {
            for (int to_square : coordinates_white_king_pre_attacks[from_square])
            {
                U64 target_mask = 1ULL << to_square;
                if(!(target_mask & white_pieces_mask) && !(target_mask & black_attacks_mask))
                {
                    white_king_moves.push_back(std::make_pair(from_square, to_square));
                }
            }
        }
        return white_king_moves;
    }
};