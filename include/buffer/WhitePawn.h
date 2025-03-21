#pragma once
#include "Pawn.h"
#include "White.h"

class WhitePawn : public Pawn, public White
{
private:
    // std::vector<int> linear_coordinates{8, 9, 10, 11, 12, 13, 14, 15};
    std::array<U64, 64> white_pawn_pre_attacks;
    std::array<U64, 64> moves_vector;
    std::array<std::vector<int>, 64> moves_vector;
    std::vector<std::pair<int, int>> moves_vector;

public:

    void CalculateWhitePawnsPreMoves()
    {
        for (int i = 8; i < 56; ++i)
        {
            int move = i + 8;
            moves_vector[i] = 1ULL << move;
            moves_vector[i].push_back(move);

            if (i / 8 == 1)
            {
                int double_step_move = i + 16;
                int one_step_move = i + 8;

                if (!(moves_vector[i] & all_pieces_mask) && !(moves_vector[one_step_move] & all_pieces_mask))
                {
                    moves_vector[i] |= 1ULL << double_step_move;
                    moves_vector[i].push_back(double_step_move);
                }
            }
        }
    }

    void CalculateWhitePawnsPreAttacks()
    {
        for (int i = 8; i < 56; ++i)
        {
            int from_rank = i / 8;
            int from_file = i % 8;

            if (from_file != 0)
            {
                int attack_left = i + 7;
                if (attack_left >= 0 && attack_left < 64)
                {
                    white_pawn_pre_attacks[i] |= 1ULL << attack_left;
                    pre_attacks_coordinates[i].push_back(attack_left);
                }
            }

            if (from_file != 7)
            {
                int attack_right = i + 9;
                if (attack_right >= 0 && attack_right < 64)
                {
                    white_pawn_pre_attacks[i] |= 1ULL << attack_right;
                    pre_attacks_coordinates[i].push_back(attack_right);
                }
            }
        }
    }

    std::vector<std::pair<int, int>> CalculateWhitePawnsMoves()
    {
        moves_vector.clear();

        for (int from_square : linear_coordinates)
        {
            for (int to_square : moves_vector[from_square])
            {
                U64 target_mask = 1ULL << to_square;
                if (!(target_mask & all_pieces_mask))
                {
                    moves_vector.emplace_back(from_square, to_square);
                }
            }

            if (from_square / 8 == 1)
            {
                int one_step_square = from_square + 8;
                int double_step_square = from_square + 16;

                U64 one_step_mask = 1ULL << one_step_square;
                U64 double_step_mask = 1ULL << double_step_square;

                if (!(one_step_mask & all_pieces_mask) && !(double_step_mask & all_pieces_mask))
                {
                    moves_vector.emplace_back(from_square, double_step_square);
                }
            }

            for (int attack_square : pre_attacks_coordinates[from_square])
            {
                U64 attack_mask = 1ULL << attack_square;
                if (attack_mask & black_pieces_mask)
                {
                    moves_vector.emplace_back(from_square, attack_square);
                    squares_controlled |= attack_square;
                }
            }
        }
        return moves_vector;
    }

    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 current_pawn_mask, std::vector<int> &linear_coordinates)
    {
        U64 from_mask = 1ULL << move_to_execute.first;
        U64 to_mask = 1ULL << move_to_execute.second;
        current_pawn_mask ^= from_mask;
        current_pawn_mask ^= to_mask;

        if (to_mask & black_pieces_mask)
        {
            MaskToCapture(to_mask, true);
        }

        if (move_to_execute.second >= 56 && move_to_execute.second <= 63)
        {
            std::vector<std::pair<int, char>> promotion_choices;
            promotion_choices.push_back({move_to_execute.second, 'Q'});
            promotion_choices.push_back({move_to_execute.second, 'R'});
            promotion_choices.push_back({move_to_execute.second, 'N'});
            promotion_choices.push_back({move_to_execute.second, 'B'});

            for (auto &promotion : promotion_choices)
            {
                char promotion_type = promotion.second;
                U64 promotion_mask = 1ULL << promotion.first;

                switch (promotion_type)
                {
                case 'Q':
                    WhiteQueen::white_queens_mask |= promotion_mask;
                    break;
                case 'R':
                    WhiteRook::white_rooks_mask |= promotion_mask;
                    break;
                case 'N':
                    WhiteKnight::white_knights_mask |= promotion_mask;
                    break;
                case 'B':
                    WhiteBishop::white_bishops_mask |= promotion_mask;
                    break;
                }
            }
        }

        for (int i = 0; i < linear_coordinates.size(); ++i)
        {
            if (linear_coordinates.at(i) == move_to_execute.first)
            {
                linear_coordinates.at(i) = move_to_execute.second;
                break;
            }
        }

        return current_pawn_mask;
    }
};





