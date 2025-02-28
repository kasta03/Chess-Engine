#pragma once
#include "Pawn.h"

class BlackPawn : public Pawn
{
private:
    std::vector<int> linear_coordinates{48, 49, 50, 51, 52, 53, 54, 55};
    std::array<U64, 64> black_pawn_pre_attacks;
    std::array<U64, 64> black_pawn_pre_moves;
    std::array<std::vector<int>, 64> coordinates_black_pawn_pre_attacks;
    std::array<std::vector<int>, 64> coordinates_black_pawn_pre_moves;
    std::vector<std::pair<int, int>> black_pawn_moves;

public:
    static bool isBlack;
    static U64 black_pawns_mask;

    void CalculateBlackPawnsPreMoves()
    {
        for (int i = 8; i < 56; ++i)
        {
            int move = i - 8;
            black_pawn_pre_moves[i] = 1ULL << move;
            coordinates_black_pawn_pre_moves[i].push_back(move);

            if (i / 8 == 6)
            {
                int double_step_move = i - 16;
                int one_step_move = i - 8;

                U64 one_step_mask = 1ULL << one_step_move;
                U64 double_step_mask = 1ULL << double_step_move;

                if (!(one_step_mask & all_pieces_mask) && !(double_step_mask & all_pieces_mask))
                {
                    black_pawn_pre_moves[i] |= double_step_mask;
                    coordinates_black_pawn_pre_moves[i].push_back(double_step_move);
                }
            }
        }
    }

    void CalculateBlackPawnsPreAttacks()
    {
        for (int i = 8; i < 56; ++i)
        {
            int from_rank = i / 8;
            int from_file = i % 8;

            if (from_file != 0)
            {
                int attack_left = i - 9;
                if (attack_left >= 0 && attack_left < 64)
                {
                    black_pawn_pre_attacks[i] |= 1ULL << attack_left;
                    coordinates_black_pawn_pre_attacks[i].push_back(attack_left);
                }
            }

            if (from_file != 7)
            {
                int attack_right = i - 7;
                if (attack_right >= 0 && attack_right < 64)
                {
                    black_pawn_pre_attacks[i] |= 1ULL << attack_right;
                    coordinates_black_pawn_pre_attacks[i].push_back(attack_right);
                }
            }
        }
    }

    std::vector<std::pair<int, int>> CalculateBlackPawnsMoves()
    {
        black_pawn_moves.clear();

        for (int from_square : linear_coordinates)
        {
            for (int to_square : coordinates_black_pawn_pre_moves[from_square])
            {
                U64 target_mask = 1ULL << to_square;
                if (!(target_mask & all_pieces_mask))
                {
                    black_pawn_moves.emplace_back(from_square, to_square);
                }
            }

            if (from_square / 8 == 6)
            {
                int one_step_square = from_square - 8;
                int double_step_square = from_square - 16;

                U64 one_step_mask = 1ULL << one_step_square;
                U64 double_step_mask = 1ULL << double_step_square;

                if (!(one_step_mask & all_pieces_mask) && !(double_step_mask & all_pieces_mask))
                {
                    black_pawn_moves.emplace_back(from_square, double_step_square);
                }
            }

            for (int attack_square : coordinates_black_pawn_pre_attacks[from_square])
            {
                U64 attack_mask = 1ULL << attack_square;
                if (attack_mask & white_pieces_mask)
                {
                    black_pawn_moves.emplace_back(from_square, attack_square);
                }
            }
        }
        return black_pawn_moves;
    }

    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 current_pawn_mask, std::vector<int>& linear_coordinates)
    {
        U64 from_mask = 1ULL << move_to_execute.first;
        U64 to_mask = 1ULL << move_to_execute.second;
        current_pawn_mask ^= from_mask;
        current_pawn_mask ^= to_mask;

        if (to_mask & white_pieces_mask)
        {
            MaskToCapture(to_mask, false);
        }

        if (move_to_execute.second <= 7 && move_to_execute.second >= 0)
        {
            std::vector<std::pair<int, char>> promotion_choices;
            promotion_choices.push_back({move_to_execute.second, 'Q'});
            promotion_choices.push_back({move_to_execute.second, 'R'});
            promotion_choices.push_back({move_to_execute.second, 'N'});
            promotion_choices.push_back({move_to_execute.second, 'B'});

            for (auto& promotion : promotion_choices)
            {
                char promotion_type = promotion.second;
                U64 promotion_mask = 1ULL << promotion.first;

                switch (promotion_type)
                {
                case 'Q':
                    BlackQueen::black_queens_mask |= promotion_mask;
                    break;
                case 'R':
                    BlackRook::black_rooks_mask |= promotion_mask;
                    break;
                case 'N':
                    BlackKnight::black_knights_mask |= promotion_mask;
                    break;
                case 'B':
                    BlackBishop::black_bishops_mask |= promotion_mask;
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
