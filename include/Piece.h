#pragma once
#include <array>
#include <utility>
#include <vector>
#include <iostream>
#include <utility>

using U64 = unsigned long long;

class Piece
{
protected:
    U64 bitboard;
    std::vector<int> linear_coordinates;
public:
    static void MaskToCapture(U64 to_mask, bool isWhite);
    static void InitializeBitboards();
    std::array<std::vector<int>, 64> pre_attacks_coordinates;
    std::vector<std::pair<int, int>> moves_vector;

    static U64 white_bitboard;
    static U64 black_bitboard;
    static U64 whole_bitboard;
    
    static std::vector<Piece*> white_pieces;
    static std::vector<Piece*> black_pieces;
};
