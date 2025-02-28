#pragma once
#include <array>
#include <utility>
#include <vector>
#include <iostream>
#include <utility>

using U64 = unsigned long long;
class Pawn;
class Knight;
class WhitePawn;

class Piece
{
    protected:
        
        U64 white_pieces_mask = 0;
        U64 black_pieces_mask = 0;
        U64 all_pieces_mask = white_pieces_mask | black_pieces_mask;
        void MaskToCapture(U64 to_mask, bool isWhite);
    public:

};