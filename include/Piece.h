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
    void MaskToCapture(U64 to_mask, bool isWhite);
public:
    static U64 white_pieces_mask;
    static U64 black_pieces_mask;
    static U64 all_pieces_mask;
    static U64 white_attacks_mask;
    static U64 black_attacks_mask;

};