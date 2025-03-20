#include "../include/Piece.h"

std::vector<Piece*> Piece::white_pieces;
std::vector<Piece*> Piece::black_pieces;

U64 Piece::white_bitboard = 0;
U64 Piece::black_bitboard = 0;
U64 Piece::whole_bitboard = 0;

void Piece::InitializeBitboards()
{
    white_bitboard = 0;
    black_bitboard = 0;
    
    for (Piece* piece : white_pieces)
    {
        white_bitboard |= piece->bitboard;
    }
    
    for (Piece* piece : black_pieces)
    {
        black_bitboard |= piece->bitboard;
    }
    
    whole_bitboard = white_bitboard | black_bitboard;
}

void Piece::MaskToCapture(U64 to_mask, bool isWhite)
{
    std::vector<Piece*>& pieces = isWhite ? white_pieces : black_pieces;
    
    for (auto it = pieces.begin(); it != pieces.end(); ++it)
    {
        if ((*it)->bitboard & to_mask)
        {
            (*it)->bitboard ^= to_mask;
            break;
        }
    }
    
    InitializeBitboards();
}
