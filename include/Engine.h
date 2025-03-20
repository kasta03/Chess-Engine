#pragma once
#include "pch.h"

struct GameState
{
    GameState()
    {
        WhitePawn white_pawn = *dynamic_cast<WhitePawn *>(Piece::white_pieces.at(0));
        WhiteKnight white_knight = *dynamic_cast<WhiteKnight *>(Piece::white_pieces.at(1));
        WhiteBishop white_bishop = *dynamic_cast<WhiteBishop *>(Piece::white_pieces.at(2));
        WhiteRook white_rook = *dynamic_cast<WhiteRook *>(Piece::white_pieces.at(3));
        WhiteQueen white_queen = *dynamic_cast<WhiteQueen *>(Piece::white_pieces.at(4));
        WhiteKing white_king = *dynamic_cast<WhiteKing *>(Piece::white_pieces.at(5));

        BlackPawn black_pawn = *dynamic_cast<BlackPawn *>(Piece::black_pieces.at(0));
        BlackKnight black_knight = *dynamic_cast<BlackKnight *>(Piece::black_pieces.at(1));
        BlackBishop black_bishop = *dynamic_cast<BlackBishop *>(Piece::black_pieces.at(2));
        BlackRook black_rook = *dynamic_cast<BlackRook *>(Piece::black_pieces.at(3));
        BlackQueen black_queen = *dynamic_cast<BlackQueen *>(Piece::black_pieces.at(4));
        BlackKing black_king = *dynamic_cast<BlackKing *>(Piece::black_pieces.at(5));
    }

    WhitePawn white_pawn;
    WhiteKnight white_knight;
    WhiteBishop white_bishop;
    WhiteRook white_rook;
    WhiteQueen white_queen;
    WhiteKing white_king;

    BlackPawn black_pawn;
    BlackKnight black_knight;
    BlackBishop black_bishop;
    BlackRook black_rook;
    BlackQueen black_queen;
    BlackKing black_king;
};

class Engine
{
    int isMove = 1;
    const std::array<float, 64> knight_table = {
        2.5, 2.7, 2.9, 2.9, 2.9, 2.9, 2.7, 2.5,
        2.7, 2.9, 3.0, 3.0, 3.0, 3.0, 2.9, 2.7,
        2.9, 3.0, 3.2, 3.3, 3.3, 3.2, 3.0, 2.9,
        2.9, 3.1, 3.3, 3.4, 3.4, 3.3, 3.1, 2.9,
        2.9, 3.0, 3.3, 3.4, 3.4, 3.3, 3.0, 2.9,
        2.9, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 2.9,
        2.7, 2.9, 3.0, 3.1, 3.1, 3.0, 2.9, 2.7,
        2.5, 2.7, 2.9, 2.9, 2.9, 2.9, 2.7, 2.5};
    const std::array<float, 64> bishop_table = {
        2.9, 3.0, 3.1, 3.1, 3.1, 3.1, 3.0, 2.9,
        3.0, 3.2, 3.3, 3.3, 3.3, 3.3, 3.2, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.1, 3.4, 3.5, 3.6, 3.6, 3.5, 3.4, 3.1,
        3.1, 3.3, 3.5, 3.6, 3.6, 3.5, 3.3, 3.1,
        3.1, 3.4, 3.4, 3.5, 3.5, 3.4, 3.4, 3.1,
        3.0, 3.2, 3.3, 3.3, 3.3, 3.3, 3.2, 3.0,
        2.9, 3.0, 3.1, 3.1, 3.1, 3.1, 3.0, 2.9};
    const std::array<float, 64> rook_table = {
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1,
        3.1, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.1,
        3.1, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.1,
        3.2, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.2,
        3.2, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.2,
        3.1, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.1,
        3.1, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.1,
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1};
    const std::array<float, 64> queen_table = {
        3.0, 3.0, 3.0, 3.1, 3.1, 3.0, 3.0, 3.0,
        3.0, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.0,
        3.0, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.0, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.0,
        3.0, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.0,
        3.0, 3.0, 3.0, 3.1, 3.1, 3.0, 3.0, 3.0};
    const std::array<float, 64> pawn_table_white = {
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1,
        3.2, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.2,
        3.3, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.3,
        3.4, 3.4, 3.5, 3.6, 3.6, 3.5, 3.4, 3.4,
        3.5, 3.5, 3.6, 3.7, 3.7, 3.6, 3.5, 3.5,
        3.6, 3.6, 3.7, 3.8, 3.8, 3.7, 3.6, 3.6,
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0};
    const std::array<float, 64> pawn_table_black = {
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
        3.6, 3.6, 3.7, 3.8, 3.8, 3.7, 3.6, 3.6,
        3.5, 3.5, 3.6, 3.7, 3.7, 3.6, 3.5, 3.5,
        3.4, 3.4, 3.5, 3.6, 3.6, 3.5, 3.4, 3.4,
        3.3, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.3,
        3.2, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.2,
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1,
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0};
    const std::array<float, 64> king_table_midgame_white = {
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0};

    const std::array<float, 64> king_table_midgame_black = {
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0};
    const std::array<float, 64> king_table_endgame_white = {
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0};

    const std::array<float, 64> king_table_endgame_black = {
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0};

public:
    float Evaluate()
    {
        float white_sum = 0;
        float black_sum = 0;

        for (int i = 0; i < Piece::white_pieces.at(0)->linear_coordinates.size(); ++i)
        {
            white_sum += pawn_table_white.at(Piece::white_pieces.at(0)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::white_pieces.at(1)->linear_coordinates.size(); ++i)
        {
            white_sum += knight_table.at(Piece::white_pieces.at(1)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::white_pieces.at(2)->linear_coordinates.size(); ++i)
        {
            white_sum += bishop_table.at(Piece::white_pieces.at(2)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::white_pieces.at(3)->linear_coordinates.size(); ++i)
        {
            white_sum += rook_table.at(Piece::white_pieces.at(3)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::white_pieces.at(4)->linear_coordinates.size(); ++i)
        {
            white_sum += queen_table.at(Piece::white_pieces.at(4)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::white_pieces.at(5)->linear_coordinates.size(); ++i)
        {
            white_sum += king_table_midgame_white.at(Piece::white_pieces.at(5)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::black_pieces.at(0)->linear_coordinates.size(); ++i)
        {
            black_sum -= pawn_table_black.at(Piece::black_pieces.at(0)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::black_pieces.at(1)->linear_coordinates.size(); ++i)
        {
            black_sum -= knight_table.at(Piece::black_pieces.at(1)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::black_pieces.at(2)->linear_coordinates.size(); ++i)
        {
            black_sum -= bishop_table.at(Piece::black_pieces.at(2)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::black_pieces.at(3)->linear_coordinates.size(); ++i)
        {
            black_sum -= rook_table.at(Piece::black_pieces.at(3)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::black_pieces.at(4)->linear_coordinates.size(); ++i)
        {
            black_sum -= queen_table.at(Piece::black_pieces.at(4)->linear_coordinates.at(i));
        }
        for (int i = 0; i < Piece::black_pieces.at(5)->linear_coordinates.size(); ++i)
        {
            black_sum -= king_table_midgame_black.at(Piece::black_pieces.at(5)->linear_coordinates.at(i));
        }
        return white_sum + black_sum;
    }

    float EvaluateCurrentPosition(WhitePawn white_pawn, WhiteKnight white_knight, WhiteBishop white_bishop, WhiteRook white_rook, WhiteQueen white_queen, WhiteKing white_king,
                                  BlackPawn black_pawn, BlackKnight black_knight, BlackBishop black_bishop, BlackRook black_rook, BlackQueen black_queen, BlackKing black_king)
    {
        float white_sum = 0;
        float black_sum = 0;

        for (int i = 0; i < white_pawn.linear_coordinates.size(); ++i)
        {
            white_sum += pawn_table_white.at(white_pawn.linear_coordinates.at(i));
        }
        for (int i = 0; i < white_knight.linear_coordinates.size(); ++i)
        {
            white_sum += knight_table.at(white_knight.linear_coordinates.at(i));
        }
        for (int i = 0; i < white_bishop.linear_coordinates.size(); ++i)
        {
            white_sum += bishop_table.at(white_bishop.linear_coordinates.at(i));
        }
        for (int i = 0; i < white_rook.linear_coordinates.size(); ++i)
        {
            white_sum += rook_table.at(white_rook.linear_coordinates.at(i));
        }
        for (int i = 0; i < white_queen.linear_coordinates.size(); ++i)
        {
            white_sum += queen_table.at(white_queen.linear_coordinates.at(i));
        }
        for (int i = 0; i < white_king.linear_coordinates.size(); ++i)
        {
            white_sum += king_table_midgame_white.at(white_king.linear_coordinates.at(i));
        }
        for (int i = 0; i < black_pawn.linear_coordinates.size(); ++i)
        {
            black_sum -= pawn_table_black.at(black_pawn.linear_coordinates.at(i));
        }
        for (int i = 0; i < black_knight.linear_coordinates.size(); ++i)
        {
            black_sum -= knight_table.at(black_knight.linear_coordinates.at(i));
        }
        for (int i = 0; i < black_bishop.linear_coordinates.size(); ++i)
        {
            black_sum -= bishop_table.at(black_bishop.linear_coordinates.at(i));
        }
        for (int i = 0; i < black_rook.linear_coordinates.size(); ++i)
        {
            black_sum -= rook_table.at(black_rook.linear_coordinates.at(i));
        }
        for (int i = 0; i < black_queen.linear_coordinates.size(); ++i)
        {
            black_sum -= queen_table.at(black_queen.linear_coordinates.at(i));
        }
        for (int i = 0; i < black_king.linear_coordinates.size(); ++i)
        {
            black_sum -= king_table_midgame_black.at(black_king.linear_coordinates.at(i));
        }

        return white_sum + black_sum;
    }

    std::vector<std::vector<Piece *>> GenerateMoves(bool isWhite, GameState &game_state)
    {
        std::vector<GameState> game_states;
        game_states.push_back(game_state);

        if (isWhite)
        {
            std::vector<std::pair<int, int>> pawn_moves = game_state.white_pawn.CalculateWhitePawnsMoves();
            for (const auto &move : pawn_moves)
            {
                game_state.white_pawn.ExecuteMove(move, game_state.white_pawn.bitboard, game_state.white_pawn.linear_coordinates);
                game_states.push_back(game_state);
            }

            std::vector<std::pair<int, int>> knight_moves = game_state.white_knight.CalculateWhiteKnightsMoves();
            for (const auto &move : knight_moves)
            {
                game_state.white_knight.ExecuteMove(move, game_state.white_knight.bitboard, game_state.white_knight.linear_coordinates);
                game_states.push_back(game_state);
            }

            std::vector<std::pair<int, int>> bishop_moves = game_state.white_bishop.CalculateWhiteBishopsMoves();
            for (const auto &move : bishop_moves)
            {
                game_state.white_bishop.ExecuteMove(move, game_state.white_bishop.bitboard, game_state.white_bishop.linear_coordinates);
                game_states.push_back(game_state);
            }

            std::vector<std::pair<int, int>> rook_moves = game_state.white_rook.CalculateWhiteRooksMoves();
            for (const auto &move : rook_moves)
            {
                game_state.white_rook.ExecuteMove(move, game_state.white_rook.bitboard, game_state.white_rook.linear_coordinates);
                game_states.push_back(game_state);
            }

            std::vector<std::pair<int, int>> queen_moves = game_state.white_queen.CalculateWhiteQueensMoves();
            for (const auto &move : queen_moves)
            {
                game_state.white_queen.ExecuteMove(move, game_state.white_queen.bitboard, game_state.white_queen.linear_coordinates);
                game_states.push_back(game_state);
            }

            std::vector<std::pair<int, int>> king_moves = game_state.white_king.CalculateWhiteKingMoves();
            for (const auto &move : king_moves)
            {
                game_state.white_king.ExecuteMove(move, game_state.white_king.bitboard, game_state.white_king.linear_coordinates);
                game_states.push_back(game_state);
            }
        }
        else
        {
            
        }
    }

    float minimax(int depth, bool maximazingColour)
    {
        if (depth == 0)
        {
            return Evaluate();
        }
        if (maximazingColour)
        {
            float maxEval = -std::numeric_limits<float>::infinity();
        }
    }

    void ExecuteMove(std::pair<int, int> move_to_execute, U64 from_mask, U64 to_mask, std::vector<int> &linear_coordinates)
    {
        from_mask ^= 1ULL << move_to_execute.first;
        from_mask ^= 1ULL << move_to_execute.second;
        if (to_mask & Piece::whole_bitboard)
        {
            Piece::MaskToCapture(to_mask, false);
        }

        for (int i = 0; i < linear_coordinates.size(); ++i)
        {
            if (linear_coordinates.at(i) == move_to_execute.first)
            {
                linear_coordinates.at(i) = move_to_execute.second;
            }
        }
        isMove = !isMove;
    }
};