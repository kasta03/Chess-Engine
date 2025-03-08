#pragma once
#include <array>
#include <utility>
#include <vector>
#include <iostream>
#include <utility>

using U64 = unsigned long long;

class Piece
{
public:
    static void MaskToCapture(U64 to_mask, bool isWhite);
    std::array<std::vector<int>, 64> pre_attacks_coordinates;
    static U64 bitboard;
    static std::vector<int> linear_coordinates;
    std::vector<std::pair<int, int>> moves_vector;

    static U64 white_bitboard;
    static U64 black_bitboard;
    static U64 whole_bitboard;
    
};
