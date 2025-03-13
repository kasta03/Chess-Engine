#include "WhitePawn.h"

bool WhitePawn::isWhite = true;
U64 WhitePawn::bitboard = 0b11111111 << 8;
std::vector<int> WhitePawn::linear_coordinates = {8, 9, 10, 11, 12, 13, 14, 15};

// void WhitePawn::getPawnsPositions()
// {
//     for (int i = 0; i < 64; ++i)
//     {
//         white_pawn_positions[i] = WhitePawn::white_pawns_mask & (1ULL << i);
//     }
// }
