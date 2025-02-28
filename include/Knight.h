#include <Piece.h>

class Knight : public Piece
{
    protected:
    
    std::array<int, 8> possible_moves = {6, 15, 17, 10, -6, -15, -17, -10};
};