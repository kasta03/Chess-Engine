#include <iostream>
#include "include/pch.h"

int main()
{
    Piece *White_Pawn = new WhitePawn();
    Piece *White_Knight = new WhiteKnight();
    Piece *White_Bishop = new WhiteBishop();
    Piece *White_Rook = new WhiteRook();
    Piece *White_Queen = new WhiteQueen();
    Piece *White_King = new WhiteKing();

    Piece::white_pieces.push_back(White_Pawn);
    Piece::white_pieces.push_back(White_Knight);
    Piece::white_pieces.push_back(White_Bishop);
    Piece::white_pieces.push_back(White_Rook);
    Piece::white_pieces.push_back(White_Queen);
    Piece::white_pieces.push_back(White_King);

    Piece *Black_Pawn = new BlackPawn();
    Piece *Black_Knight = new BlackKnight();
    Piece *Black_Bishop = new BlackBishop();
    Piece *Black_Rook = new BlackRook();
    Piece *Black_Queen = new BlackQueen();
    Piece *Black_King = new BlackKing();

    Piece::black_pieces.push_back(Black_Pawn);
    Piece::black_pieces.push_back(Black_Knight);
    Piece::black_pieces.push_back(Black_Bishop);
    Piece::black_pieces.push_back(Black_Rook);
    Piece::black_pieces.push_back(Black_Queen);
    Piece::black_pieces.push_back(Black_King);

    Piece::InitializeBitboards();

    print_bitboard();

    return 0;
}
