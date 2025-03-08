#pragma once
#include "Piece.h"

U64 Piece::white_bitboard = WhitePawn::bitboard | WhiteKnight::bitboard | WhiteBishop::bitboard | WhiteRook::bitboard | WhiteQueen::bitboard | WhiteKing::bitboard;
U64 Piece::black_bitboard = BlackPawn::bitboard | BlackKnight::bitboard | BlackBishop::bitboard | BlackRook::bitboard | BlackQueen::bitboard | BlackKing::bitboard;
U64 Piece::whole_bitboard = Piece::white_bitboard | Piece::black_bitboard;

void Piece::MaskToCapture(U64 to_mask, bool isWhite)
{
    if(isWhite)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (to_mask & WhitePawn::bitboard)
            {
                WhitePawn::bitboard ^ to_mask;
            }
            else if (to_mask & WhiteKnight::bitboard)
            {
                WhiteKnight::bitboard ^ to_mask;
            }
            else if (to_mask & WhiteBishop::bitboard)
            {
                WhiteBishop::bitboard ^ to_mask;
            }
            else if (to_mask & WhiteRook::bitboard)
            {
                WhiteRook::bitboard ^ to_mask;
            }
            else if (to_mask & WhiteQueen::bitboard)
            {
                WhiteQueen::bitboard ^ to_mask;
            }
            else if (to_mask & WhiteKing::bitboard)
            {
                WhiteKing::bitboard ^ to_mask;
            }
        }
    }
    else
    {
        for (int i = 0; i < 6; ++i)
        {
            if (to_mask & BlackPawn::bitboard)
            {
                BlackPawn::bitboard ^ to_mask;
            }
            else if (to_mask & BlackKnight::bitboard)
            {
                BlackKnight::bitboard ^ to_mask;
            }
            else if (to_mask & BlackBishop::bitboard)
            {
                BlackBishop::bitboard ^ to_mask;
            }
            else if (to_mask & BlackRook::bitboard)
            {
                BlackRook::bitboard ^ to_mask;
            }
            else if (to_mask & BlackQueen::bitboard)
            {
                BlackQueen::bitboard ^ to_mask;
            }
            else if (to_mask & BlackKing::bitboard)
            {
                BlackKing::bitboard ^ to_mask;
            }
        }
    }
}