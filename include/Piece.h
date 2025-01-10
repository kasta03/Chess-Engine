#pragma once
#include <array>
#include <utility>
#include <vector>
#include <iostream>

using U64 = unsigned long long;

class Piece
{
    U64 white_pieces_mask = 0;
    U64 black_pieces_mask = 0;
    U64 all_pieces_mask = white_pieces_mask | black_pieces_mask;
    public:

};