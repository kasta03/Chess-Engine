#pragma once
#include "Piece.h"
#include "WhitePawn.h"
#include "WhiteKnight.h"
#include "WhiteBishop.h"
#include "WhiteRook.h"
#include "WhiteQueen.h"
#include "WhiteKing.h"
#include "BlackPawn.h"
#include "BlackKnight.h"
#include "BlackBishop.h"
#include "BlackRook.h"
#include "BlackQueen.h"
#include "BlackKing.h"

class Engine
{
    int isMove = 1;
    const std::array<float, 64> knight_table = {
        2.5, 2.7, 2.9, 2.9, 2.9, 2.9, 2.7, 2.5,
        2.7, 2.9, 3.0, 3.0, 3.0, 3.0, 2.9, 2.7,
        2.9, 3.0, 3.2, 3.3, 3.3, 3.2, 3.0, 2.9,
        2.9, 3.1, 3.3, 3.4, 3.4, 3.3, 3.1, 2.9,
        2.9, 3.0, 3.3, 3.4, 3.4, 3.3, 3.0, 2.9,
        2.9, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 2.9,
        2.7, 2.9, 3.0, 3.1, 3.1, 3.0, 2.9, 2.7,
        2.5, 2.7, 2.9, 2.9, 2.9, 2.9, 2.7, 2.5
    };
    const std::array<float, 64> bishop_table = {
        2.9, 3.0, 3.1, 3.1, 3.1, 3.1, 3.0, 2.9,
        3.0, 3.2, 3.3, 3.3, 3.3, 3.3, 3.2, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.1, 3.4, 3.5, 3.6, 3.6, 3.5, 3.4, 3.1,
        3.1, 3.3, 3.5, 3.6, 3.6, 3.5, 3.3, 3.1,
        3.1, 3.4, 3.4, 3.5, 3.5, 3.4, 3.4, 3.1,
        3.0, 3.2, 3.3, 3.3, 3.3, 3.3, 3.2, 3.0,
        2.9, 3.0, 3.1, 3.1, 3.1, 3.1, 3.0, 2.9
    };
    const std::array<float, 64> rook_table = {
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1,
        3.1, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.1,
        3.1, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.1,
        3.2, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.2,
        3.2, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.2,
        3.1, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.1,
        3.1, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.1,
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1
    };
    const std::array<float, 64> queen_table = {
        3.0, 3.0, 3.0, 3.1, 3.1, 3.0, 3.0, 3.0,
        3.0, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.0,
        3.0, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.0, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.0,
        3.0, 3.2, 3.2, 3.3, 3.3, 3.2, 3.2, 3.0,
        3.0, 3.0, 3.0, 3.1, 3.1, 3.0, 3.0, 3.0
    };
    const std::array<float, 64> pawn_table_white = {
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1,
        3.2, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.2,
        3.3, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.3,
        3.4, 3.4, 3.5, 3.6, 3.6, 3.5, 3.4, 3.4,
        3.5, 3.5, 3.6, 3.7, 3.7, 3.6, 3.5, 3.5,
        3.6, 3.6, 3.7, 3.8, 3.8, 3.7, 3.6, 3.6,
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0
    };
    const std::array<float, 64> pawn_table_black = {
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0,
        3.6, 3.6, 3.7, 3.8, 3.8, 3.7, 3.6, 3.6,
        3.5, 3.5, 3.6, 3.7, 3.7, 3.6, 3.5, 3.5,
        3.4, 3.4, 3.5, 3.6, 3.6, 3.5, 3.4, 3.4,
        3.3, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.3,
        3.2, 3.2, 3.3, 3.4, 3.4, 3.3, 3.2, 3.2,
        3.1, 3.1, 3.1, 3.2, 3.2, 3.1, 3.1, 3.1,
        3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0, 3.0
    };
    const std::array<float, 64> king_table_midgame_white = {
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0
    };
    
    const std::array<float, 64> king_table_midgame_black = {
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.3, 2.4, 2.4, 2.4, 2.4, 2.3, 2.0,
        2.0, 2.2, 2.3, 2.3, 2.3, 2.3, 2.2, 2.0,
        2.0, 2.2, 2.2, 2.1, 2.1, 2.2, 2.2, 2.0,
        2.0, 2.1, 2.1, 2.0, 2.0, 2.1, 2.1, 2.0
    };
    const std::array<float, 64> king_table_endgame_white = {
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0
    };
    
    const std::array<float, 64> king_table_endgame_black = {
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.3, 3.5, 3.7, 3.8, 3.8, 3.7, 3.5, 3.3,
        3.2, 3.4, 3.6, 3.7, 3.7, 3.6, 3.4, 3.2,
        3.1, 3.3, 3.4, 3.5, 3.5, 3.4, 3.3, 3.1,
        3.0, 3.1, 3.2, 3.3, 3.3, 3.2, 3.1, 3.0
    };
    

public:
    float Evaluate()
    {
        float white_sum = 0;
        float black_sum = 0;
        
        for(int i = 0; i < WhitePawn::linear_coordinates.size(); ++i)
        {
            white_sum += pawn_table_white.at(WhitePawn::linear_coordinates.at(i));
        } 
        for(int i = 0; i < WhiteKnight::linear_coordinates.size(); ++i)
        {
            white_sum += knight_table.at(WhiteKnight::linear_coordinates.at(i));
        }
        for(int i = 0; i < WhiteBishop::linear_coordinates.size(); ++i)
        {
            white_sum += bishop_table.at(WhiteBishop::linear_coordinates.at(i));
        }
        for(int i = 0; i < WhiteRook::linear_coordinates.size(); ++i)
        {
            white_sum += rook_table.at(WhiteRook::linear_coordinates.at(i));
        }
        for(int i = 0; i < WhiteQueen::linear_coordinates.size(); ++i)
        {
            white_sum += queen_table.at(WhiteQueen::linear_coordinates.at(i));
        }
        for(int i = 0; i < WhiteKing::linear_coordinates.size(); ++i)
        {
            white_sum += king_table_midgame_white.at(WhiteKing::linear_coordinates.at(i));
        }
        for(int i = 0; i < BlackPawn::linear_coordinates.size(); ++i)
        {
            black_sum += pawn_table_black.at(BlackPawn::linear_coordinates.at(i));
        }
        for(int i = 0; i < BlackKnight::linear_coordinates.size(); ++i)
        {
            black_sum += knight_table.at(BlackKnight::linear_coordinates.at(i));
        }
        for(int i = 0; i < BlackBishop::linear_coordinates.size(); ++i)
        {
            black_sum += bishop_table.at(BlackBishop::linear_coordinates.at(i));
        }
        for(int i = 0; i < BlackRook::linear_coordinates.size(); ++i)
        {
            black_sum += rook_table.at(BlackRook::linear_coordinates.at(i));
        }
        for(int i = 0; i < BlackQueen::linear_coordinates.size(); ++i)
        {
            black_sum += queen_table.at(BlackQueen::linear_coordinates.at(i));
        }
        for(int i = 0; i < BlackKing::linear_coordinates.size(); ++i)
        {
            black_sum += king_table_midgame_black.at(BlackKing::linear_coordinates.at(i));
        }
        return white_sum - black_sum;
    }

    void ExecuteMove(std::pair<int, int> move_to_execute, U64 from_mask, U64 to_mask, std::vector<int>& linear_coordinates)
    {
        from_mask ^= 1ULL << move_to_execute.first;
        from_mask ^= 1ULL << move_to_execute.second;
        if (to_mask & Piece::whole_bitboard)
        {
            Piece::MaskToCapture(to_mask, false);
        }

        for (int i = 0; i < linear_coordinates.size(); ++i)
        {
            if (linear_coordinates.at(i) == move_to_execute.first)
            {
                linear_coordinates.at(i) = move_to_execute.second;
            }
        }
        isMove ^= 1;
    }
};  