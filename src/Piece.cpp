#pragma once
#include "Piece.h"

U64 Piece::white_pieces_mask = WhitePawn::white_pawns_mask | WhiteKnight::white_knights_mask | WhiteBishop::white_bishops_mask | WhiteRook::white_rooks_mask | WhiteQueen::white_queens_mask | WhiteKing::white_king_mask;
U64 Piece::black_pieces_mask = BlackPawn::black_pawns_mask | BlackKnight::black_knights_mask | BlackBishop::black_bishops_mask | BlackRook::black_rooks_mask | BlackQueen::black_queens_mask | BlackKing::black_king_mask;
U64 Piece::all_pieces_mask = Piece::white_pieces_mask | Piece::black_pieces_mask;

void MaskToCapture(U64 to_mask, bool isWhite)
{
    if(isWhite)
    {
        for (int i = 0; i < 6; ++i)
        {
            if (to_mask & WhitePawn::white_pawns_mask)
            {
                WhitePawn::white_pawns_mask ^ to_mask;
            }
            else if (to_mask & WhiteKnight::white_knights_mask)
            {
                WhiteKnight::white_knights_mask ^ to_mask;
            }
            else if (to_mask & WhiteBishop::white_bishops_mask)
            {
                WhiteBishop::white_bishops_mask ^ to_mask;
            }
            else if (to_mask & WhiteRook::white_rooks_mask)
            {
                WhiteRook::white_rooks_mask ^ to_mask;
            }
            else if (to_mask & WhiteQueen::white_queens_mask)
            {
                WhiteQueen::white_queens_mask ^ to_mask;
            }
            else if (to_mask & WhiteKing::white_king_mask)
            {
                WhiteKing::white_king_mask ^ to_mask;
            }
        }
    }
    else
    {
        for (int i = 0; i < 6; ++i)
        {
            if (to_mask & BlackPawn::black_pawns_mask)
            {
                BlackPawn::black_pawns_mask ^ to_mask;
            }
            else if (to_mask & BlackKnight::black_knights_mask)
            {
                BlackKnight::black_knights_mask ^ to_mask;
            }
            else if (to_mask & BlackBishop::black_bishops_mask)
            {
                BlackBishop::black_bishops_mask ^ to_mask;
            }
            else if (to_mask & BlackRook::black_rooks_mask)
            {
                BlackRook::black_rooks_mask ^ to_mask;
            }
            else if (to_mask & BlackQueen::black_queens_mask)
            {
                BlackQueen::black_queens_mask ^ to_mask;
            }
            else if (to_mask & BlackKing::black_king_mask)
            {
                BlackKing::black_king_mask ^ to_mask;
            }
        }
    }
}