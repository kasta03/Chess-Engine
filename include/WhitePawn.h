#pragma once
#include "Pawn.h"
#include "White.h"

class WhitePawn : public Pawn, public White
{
private:
    // std::vector<int> linear_coordinates{8, 9, 10, 11, 12, 13, 14, 15};
    std::array<U64, 64> white_pawn_pre_attacks;
    std::array<U64, 64> white_pawn_pre_moves;
    std::array<std::vector<int>, 64> coordinates_white_pawn_pre_moves;
    std::vector<std::pair<int, int>> white_pawn_moves;

public:
    WhitePawn(U64 bitboard = U64(0b11111111) << 8, std::vector<int> linear_coordinates = {8, 9, 10, 11, 12, 13, 14, 15}) : Piece(bitboard, linear_coordinates)
    {
        CalculateWhitePawnsPreMoves();
        CalculateWhitePawnsPreAttacks();
    }

    void CalculateWhitePawnsPreMoves()
    {
        for (int i = 8; i < 56; ++i)
        {
            int move = i + 8;
            white_pawn_pre_moves[i] = 1ULL << move;
            coordinates_white_pawn_pre_moves[i].push_back(move);

            if (i / 8 == 1)
            {
                int double_step_move = i + 16;
                int one_step_move = i + 8;

                if (!(white_pawn_pre_moves[i] & whole_bitboard) && !(white_pawn_pre_moves[one_step_move] & whole_bitboard))
                {
                    white_pawn_pre_moves[i] |= 1ULL << double_step_move;
                    coordinates_white_pawn_pre_moves[i].push_back(double_step_move);
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
        white_pawn_moves.clear();

        for (int from_square : linear_coordinates)
        {
            for (int to_square : coordinates_white_pawn_pre_moves[from_square])
            {
                U64 target_mask = 1ULL << to_square;
                if (!(target_mask & whole_bitboard))
                {
                    white_pawn_moves.emplace_back(from_square, to_square);
                }
            }

            if (from_square / 8 == 1)
            {
                int one_step_square = from_square + 8;
                int double_step_square = from_square + 16;

                U64 one_step_mask = 1ULL << one_step_square;
                U64 double_step_mask = 1ULL << double_step_square;

                if (!(one_step_mask & whole_bitboard) && !(double_step_mask & whole_bitboard))
                {
                    white_pawn_moves.emplace_back(from_square, double_step_square);
                }
            }

            for (int attack_square : pre_attacks_coordinates[from_square])
            {
                U64 attack_mask = 1ULL << attack_square;
                if (attack_mask & black_bitboard)
                {
                    white_pawn_moves.emplace_back(from_square, attack_square);
                    squares_controlled |= attack_square;
                }
            }
        }
        return white_pawn_moves;
    }

    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 from_square_mask, std::vector<int>& linear_coordinates, GameState& game_state, bool isWhite)
    {
        U64 from_mask = 1ULL << move_to_execute.first;
        U64 to_mask = 1ULL << move_to_execute.second;
        from_square_mask ^= from_mask;
        from_square_mask ^= to_mask;

        if (to_mask & game_state.black_bitboard)
        {
            MaskToCapture(to_mask, true, game_state);
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

                // switch (promotion_type)
                // {
                // case 'Q':
                //     WhiteQueen::white_queens_mask |= promotion_mask;
                //     break;
                // case 'R':
                //     WhiteRook::white_rooks_mask |= promotion_mask;
                //     break;
                // case 'N':
                //     WhiteKnight::white_knights_mask |= promotion_mask;
                //     break;
                // case 'B':
                //     WhiteBishop::white_bishops_mask |= promotion_mask;
                //     break;
                // }
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

        return from_square_mask;
    }
};




