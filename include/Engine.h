#pragma once
#include "pch.h"

class GameState
{
public:
    GameState()
        : white_pawn(WhitePawn()), white_knight(WhiteKnight()), white_bishop(WhiteBishop()), white_rook(WhiteRook()), white_queen(WhiteQueen()), white_king(WhiteKing()),
          black_pawn(BlackPawn()), black_knight(BlackKnight()), black_bishop(BlackBishop()), black_rook(BlackRook()), black_queen(BlackQueen()), black_king(BlackKing())
    {
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

    std::vector<Piece *> white_pieces = {&white_pawn, &white_knight, &white_bishop, &white_rook, &white_queen, &white_king};
    std::vector<Piece *> black_pieces = {&black_pawn, &black_knight, &black_bishop, &black_rook, &black_queen, &black_king};

    U64 white_bitboard = white_pawn.bitboard | white_knight.bitboard | white_bishop.bitboard | white_rook.bitboard | white_queen.bitboard | white_king.bitboard;
    U64 black_bitboard = black_pawn.bitboard | black_knight.bitboard | black_bishop.bitboard | black_rook.bitboard | black_queen.bitboard | black_king.bitboard;
    U64 whole_bitboard = white_bitboard | black_bitboard;
};

class Engine
{
    int evaluation = 0;
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

    float EvaluateCurrentPosition(GameState &game_state)
    {
        float white_sum = 0;
        float black_sum = 0;

        for (int i = 0; i < game_state.white_pawn.linear_coordinates.size(); ++i)
        {
            white_sum += pawn_table_white.at(game_state.white_pawn.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.white_knight.linear_coordinates.size(); ++i)
        {
            white_sum += knight_table.at(game_state.white_knight.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.white_bishop.linear_coordinates.size(); ++i)
        {
            white_sum += bishop_table.at(game_state.white_bishop.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.white_rook.linear_coordinates.size(); ++i)
        {
            white_sum += rook_table.at(game_state.white_rook.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.white_queen.linear_coordinates.size(); ++i)
        {
            white_sum += queen_table.at(game_state.white_queen.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.white_king.linear_coordinates.size(); ++i)
        {
            white_sum += king_table_midgame_white.at(game_state.white_king.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.black_pawn.linear_coordinates.size(); ++i)
        {
            black_sum -= pawn_table_black.at(game_state.black_pawn.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.black_knight.linear_coordinates.size(); ++i)
        {
            black_sum -= knight_table.at(game_state.black_knight.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.black_bishop.linear_coordinates.size(); ++i)
        {
            black_sum -= bishop_table.at(game_state.black_bishop.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.black_rook.linear_coordinates.size(); ++i)
        {
            black_sum -= rook_table.at(game_state.black_rook.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.black_queen.linear_coordinates.size(); ++i)
        {
            black_sum -= queen_table.at(game_state.black_queen.linear_coordinates.at(i));
        }
        for (int i = 0; i < game_state.black_king.linear_coordinates.size(); ++i)
        {
            black_sum -= king_table_midgame_black.at(game_state.black_king.linear_coordinates.at(i));
        }
        return white_sum + black_sum;
    }

    std::pair<int, int> GenerateMoves(bool isWhite, GameState &game_state, int depth, bool maximazingColour, int counter = 0)
    {
        std::vector<GameState> game_states;
        game_states.push_back(game_state);
        if (maximazingColour && counter == 0)
        {
            evaluation = -std::numeric_limits<float>::infinity();
        }
        else if (!maximazingColour && counter == 0)
        {
            evaluation = std::numeric_limits<float>::infinity();
        }
        if (depth == 0 && EvaluateCurrentPosition(game_state) > evaluation && isWhite)
        {
            evaluation = EvaluateCurrentPosition(game_state);
        }
        else if (depth == 0 && EvaluateCurrentPosition(game_state) < evaluation && !isWhite)
        {
            evaluation = EvaluateCurrentPosition(game_state);
        }
        if (depth == 0)
        {
            return std::make_pair(evaluation, counter);
        }
        if (isWhite)
        {
            std::vector<std::pair<int, int>> pawn_moves = game_state.white_pawn.CalculateWhitePawnsMoves();
            for (const auto &move : pawn_moves)
            {
                game_state.white_pawn.ExecuteMove(move, game_state.white_pawn.bitboard, game_state.white_pawn.linear_coordinates, game_state, counter);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }

            std::vector<std::pair<int, int>> knight_moves = game_state.white_knight.CalculateWhiteKnightsMoves();
            for (const auto &move : knight_moves)
            {
                game_state.white_knight.ExecuteMove(move, game_state.white_knight.bitboard, game_state.white_knight.linear_coordinates, game_state, counter);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }

            std::vector<std::pair<int, int>> bishop_moves = game_state.white_bishop.CalculateWhiteBishopsMoves();
            for (const auto &move : bishop_moves)
            {
                game_state.white_bishop.ExecuteMove(move, game_state.white_bishop.bitboard, game_state.white_bishop.linear_coordinates, game_state, counter);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }

            std::vector<std::pair<int, int>> rook_moves = game_state.white_rook.CalculateWhiteRooksMoves();
            for (const auto &move : rook_moves)
            {
                game_state.white_rook.ExecuteMove(move, game_state.white_rook.bitboard, game_state.white_rook.linear_coordinates, game_state, counter);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }

            std::vector<std::pair<int, int>> queen_moves = game_state.white_queen.CalculateWhiteQueensMoves();
            for (const auto &move : queen_moves)
            {
                game_state.white_queen.ExecuteMove(move, game_state.white_queen.bitboard, game_state.white_queen.linear_coordinates, game_state, counter);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }

            std::vector<std::pair<int, int>> king_moves = game_state.white_king.CalculateWhiteKingMoves();
            for (const auto &move : king_moves)
            {
                game_state.white_king.ExecuteMove(move, game_state.white_king.bitboard, game_state.white_king.linear_coordinates, game_state, counter);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
        }
        else
        {
            std::vector<std::pair<int, int>> pawn_moves = game_state.black_pawn.CalculateBlackPawnsMoves();
            for (const auto &move : pawn_moves)
            {
                game_state.black_pawn.ExecuteMove(move, game_state.black_pawn.bitboard, game_state.black_pawn.linear_coordinates, game_state, false);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
            std::vector<std::pair<int, int>> knight_moves = game_state.black_knight.CalculateBlackKnightsMoves();
            for (const auto &move : knight_moves)
            {
                game_state.black_knight.ExecuteMove(move, game_state.black_knight.bitboard, game_state.black_knight.linear_coordinates, game_state, false);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
            std::vector<std::pair<int, int>> bishop_moves = game_state.black_bishop.CalculateBlackBishopsMoves();
            for (const auto &move : bishop_moves)
            {
                game_state.black_bishop.ExecuteMove(move, game_state.black_bishop.bitboard, game_state.black_bishop.linear_coordinates, game_state, false);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
            std::vector<std::pair<int, int>> rook_moves = game_state.black_rook.CalculateBlackRooksMoves();
            for (const auto &move : rook_moves)
            {
                game_state.black_rook.ExecuteMove(move, game_state.black_rook.bitboard, game_state.black_rook.linear_coordinates, game_state, false);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
            std::vector<std::pair<int, int>> queen_moves = game_state.black_queen.CalculateBlackQueensMoves();
            for (const auto &move : queen_moves)
            {
                game_state.black_queen.ExecuteMove(move, game_state.black_queen.bitboard, game_state.black_queen.linear_coordinates, game_state, false);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
            std::vector<std::pair<int, int>> king_moves = game_state.black_king.CalculateBlackKingMoves();
            for (const auto &move : king_moves)
            {
                game_state.black_king.ExecuteMove(move, game_state.black_king.bitboard, game_state.black_king.linear_coordinates, game_state, false);
                game_states.push_back(game_state);
                GenerateMoves(!isWhite, game_state, depth - 1, maximazingColour, ++counter);
            }
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

    // void ExecuteMove(std::pair<int, int> move_to_execute, U64 from_mask, U64 to_mask, std::vector<int> &linear_coordinates, GameState &game_state)
    // {
    //     from_mask ^= 1ULL << move_to_execute.first;
    //     from_mask ^= 1ULL << move_to_execute.second;
    //     if (to_mask & Piece::whole_bitboard)
    //     {
    //         Piece::MaskToCapture(to_mask, false, game_state);
    //     }

    //     for (int i = 0; i < linear_coordinates.size(); ++i)
    //     {
    //         if (linear_coordinates.at(i) == move_to_execute.first)
    //         {
    //             linear_coordinates.at(i) = move_to_execute.second;
    //         }
    //     }
    //     isMove = !isMove;
    // }
};