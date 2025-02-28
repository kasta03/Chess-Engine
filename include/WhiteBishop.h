#pragma once
#include "Bishop.h"

class WhiteBishop : public Bishop
{
private:

    std::vector<int> linear_coordinates {2, 5};
    std::array<std::vector<int>, 64> coordinates_white_bishops_pre_attacks;
    std::vector<std::pair<int, int>> white_bishops_moves{};

public:

    static bool isWhite;
    static U64 white_bishops_mask;

    void CalculateWhiteBishopsPreAttacks()
    {        
        for (int i = 0; i < 64; ++i)
        {
            int from_rank = i / 8;
            int from_file = i % 8;
            for (auto each : possible_moves)
            {
                int to_square = i + each;
                if (to_square >= 0 && to_square < 64)
                {
                    int to_rank = to_square / 8;
                    int to_file = to_square % 8;

                    while(std::abs(from_rank - to_rank) == 1 && std::abs(from_file - to_file) == 1 && to_square >= 0 && to_square < 64)
                    {
                        coordinates_white_bishops_pre_attacks.at(i).push_back(to_square);
                        to_square += each;
                    }
                }
            }    
        }
    }
    std::vector<std::pair<int, int>> CalculateWhiteBishopsMoves()
    {
        white_bishops_moves.clear();
       
        for (int from_square : linear_coordinates)
        {
            const auto& attacks = coordinates_white_bishops_pre_attacks.at(from_square);
            for (size_t i = 0; i < attacks.size(); ++i)
            {
                int to_square = attacks[i];
                U64 target_mask = 1ULL << to_square;
                
                if(!(target_mask & all_pieces_mask))
                {
                    white_bishops_moves.push_back(std::make_pair(from_square, to_square));
                }
                else if (target_mask & black_pieces_mask)
                {
                    white_bishops_moves.push_back(std::make_pair(from_square, to_square));

                    int current_direction = to_square - from_square;
                    
                    while (i + 1 < attacks.size() && 
                            (attacks[i+1] - from_square) / abs(attacks[i+1] - from_square) == 
                            current_direction / abs(current_direction))
                    {
                        ++i;
                    }
                }
                else
                {
                    int current_direction = to_square - from_square;
                    
                    while (i + 1 < attacks.size() && 
                            (attacks[i+1] - from_square) / abs(attacks[i+1] - from_square) == 
                            current_direction / abs(current_direction))
                    {
                        ++i;
                    }
                }
            }
        }
        return white_bishops_moves;
    }
    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 from_square_bishop_mask, std::vector<int>& linear_coordinates)
    {
        U64 from_mask = 1ULL << move_to_execute.first;
        U64 to_mask = 1ULL << move_to_execute.second;
        from_square_bishop_mask ^= from_mask;
        from_square_bishop_mask ^= to_mask;
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
        return from_square_bishop_mask;
    }
};