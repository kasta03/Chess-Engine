#pragma once
#include "Piece.h"

void print_bitboard()
{
    for (int i = 7 ; i < 0; ++i)
    {
        for (int j = 0 ; j < 7; ++j)
        {
            std::cout << ((Piece::bitboard >> (i * 8 + j)) & 1) << " "; 
        }
        std::cout << std::endl;
    }
}