#pragma once
#include "pch.h"
#include <array>
#include <utility>
#include <vector>
#include <iostream>
#include <utility>

using U64 = unsigned long long;

class Piece
{
    friend class GameState;
    friend class Engine;
    friend void PrintBitboard();
protected:
    U64 bitboard;
    std::vector<int> linear_coordinates;
public:
    Piece(U64 bitboard, std::vector<int> initial_coordinates) : bitboard(bitboard), linear_coordinates(initial_coordinates) {};
    virtual ~Piece() = default;

    // virtual void CalculatePreAttacks();
    // virtual std::vector<std::pair<int, int>> CalculateMoves();
    // virtual U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 current_piece_mask, std::vector<int>& linear_coordinates);

    static void MaskToCapture(U64 to_mask, bool isWhite, GameState& game_state);
    static void InitializeBitboards(GameState& game_state);
    
    std::array<std::vector<int>, 64> pre_attacks_coordinates;
    std::vector<std::pair<int, int>> moves_vector;

    static U64 white_bitboard;
    static U64 black_bitboard;
    static U64 whole_bitboard;
    
    static std::vector<Piece*> white_pieces;
    static std::vector<Piece*> black_pieces;

    U64 ExecuteMove(std::pair<int, int> move_to_execute, U64 from_square_mask, std::vector<int>& linear_coordinates, GameState& game_state, bool isWhite);
};
