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
        
        for (int current : linear_coordinates)
        {
            for (int i = 0; i < coordinates_white_bishops_pre_attacks.at(current).size(); ++i)
            {
                int to_coordinate = coordinates_white_bishops_pre_attacks.at(current).at(i);
                int next_coordinate = coordinates_white_bishops_pre_attacks.at(current).at(i + 1);
                U64 target_mask = 1ULL << to_coordinate;
                int to_direction = to_coordinate - current > 0 ? to_coordinate - current : current - to_coordinate;
                int next_direction = next_coordinate - current > 0 ? next_coordinate - current : current - next_coordinate;
                
                if(!(target_mask & all_pieces_mask))
                {
                    white_bishops_moves.push_back(std::make_pair(current, to_coordinate));
                }
                else if (target_mask & black_pieces_mask)
                {
                    white_bishops_moves.push_back(std::make_pair(current, to_coordinate));
                    while(to_direction == next_direction)
                    {
                        ++i;
                        int to_coordinate = coordinates_white_bishops_pre_attacks.at(current).at(i);
                        int next_coordinate = coordinates_white_bishops_pre_attacks.at(current).at(i + 1);
                        int to_direction = to_coordinate - current > 0 ? to_coordinate - current : current - to_coordinate;
                        int next_direction = next_coordinate - current > 0 ? next_coordinate - current : current - next_coordinate;
                    }
                }
            }
        }
        return white_bishops_moves;
    }

};