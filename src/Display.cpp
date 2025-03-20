#include "../include/Display.h"

void PrintBitboard()
{
    for (int i = 7; i >= 0; --i)
    {
        for (int j = 0; j <= 7; ++j)
        {
            U64 square_mask = 1ULL << (i * 8 + j);

            if (Piece::white_pieces.at(0)->bitboard & square_mask)
                std::cout << WHITE << "P " << RESET;
            else if (Piece::white_pieces.at(1)->bitboard & square_mask)
                std::cout << WHITE << "N " << RESET;
            else if (Piece::white_pieces.at(2)->bitboard & square_mask)
                std::cout << WHITE << "B " << RESET;
            else if (Piece::white_pieces.at(3)->bitboard & square_mask)
                std::cout << WHITE << "R " << RESET;
            else if (Piece::white_pieces.at(4)->bitboard & square_mask)
                std::cout << WHITE << "Q " << RESET;
            else if (Piece::white_pieces.at(5)->bitboard & square_mask)
                std::cout << WHITE << "K " << RESET;
            else if (Piece::black_pieces.at(0)->bitboard & square_mask)
                std::cout << BLACK << "P " << RESET;
            else if (Piece::black_pieces.at(1)->bitboard & square_mask)
                std::cout << BLACK << "N " << RESET;
            else if (Piece::black_pieces.at(2)->bitboard & square_mask)
                std::cout << BLACK << "B " << RESET;
            else if (Piece::black_pieces.at(3)->bitboard & square_mask)
                std::cout << BLACK << "R " << RESET;
            else if (Piece::black_pieces.at(4)->bitboard & square_mask)
                std::cout << BLACK << "Q " << RESET;
            else if (Piece::black_pieces.at(5)->bitboard & square_mask)
                std::cout << BLACK << "K " << RESET;
            else
                std::cout << ". ";
        }
        std::cout << std::endl;
    }
}
