#pragma once
#include "Rook.h"

class BlackRook : public Rook
{
public:
    BlackRook(U64 bitboard = U64(0b10000001) << 56, std::vector<int> linear_coordinates = {56, 63}) : Piece(bitboard, linear_coordinates)
    {
        CalculateBlackRooksPreAttacks();
    }
    void CalculateBlackRooksPreAttacks()
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

                    if (each == -8 || each == 8)
                    {
                        while (std::abs(from_file - to_file) == 0 && to_square >= 0 && to_square < 64)
                        {
                            pre_attacks_coordinates.at(i).push_back(to_square);
                            to_square += each;
                        }
                    }
                    else
                    {
                        while (std::abs(from_rank - to_rank) == 0 && to_square >= 0 && to_square < 64)
                        {
                            pre_attacks_coordinates.at(i).push_back(to_square);
                            to_square += each;
                        }
                    }
                }
            }
        }
    }

    std::vector<std::pair<int, int>> CalculateBlackRooksMoves()
    {
        moves_vector.clear();

        for (int from_square : linear_coordinates)
        {
            const auto &attacks = pre_attacks_coordinates.at(from_square);
            for (size_t i = 0; i < attacks.size(); ++i)
            {
                int to_square = attacks[i];
                U64 target_mask = 1ULL << to_square;

                if (!(target_mask & whole_bitboard))
                {
                    moves_vector.push_back(std::make_pair(from_square, to_square));
                }
                else if (target_mask & white_bitboard)
                {
                    moves_vector.push_back(std::make_pair(from_square, to_square));

                    int current_direction = to_square - from_square;

                    if (current_direction > 1 || current_direction < -1)
                    {
                        current_direction = current_direction > 0 ? 8 : -8;
                    }

                    while (i + 1 < attacks.size() &&
                           (attacks[i + 1] - from_square) / abs(current_direction) == 1)
                    {
                        ++i;
                    }
                }
                else
                {
                    int current_direction = to_square - from_square;
                    if (current_direction > 1 || current_direction < -1)
                    {
                        current_direction = current_direction > 0 ? 8 : -8;
                    }

                    while (i + 1 < attacks.size() &&
                           (attacks[i + 1] - from_square) / abs(current_direction) == 1)
                    {
                        ++i;
                    }
                }
            }
        }
        return moves_vector;
    }

    // U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 from_square_rook_mask, std::vector<int> &linear_coordinates)
    // {
    //     U64 from_mask = 1ULL << move_to_execute.first;
    //     U64 to_mask = 1ULL << move_to_execute.second;
    //     from_square_rook_mask ^= from_mask;
    //     from_square_rook_mask ^= to_mask;
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

    //     return from_square_rook_mask;
    // }
};
