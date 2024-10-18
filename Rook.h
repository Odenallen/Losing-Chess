//
// DD1388 - Lab 4: Losing Chess
//

#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"


class Rook : virtual public ChessPiece {
    // Override virtual methods from ChessPiece here
    public:
    using ChessPiece::ChessPiece;
    char latin1Representation()override;
    string utfRepresentation()override; 
    int validMove(int to_x, int to_y)override;
    // vector<ChessMove> pathMove(int xstart,int ystart); 
    vector<ChessMove> capturingMoves()override;
    vector<ChessMove> nonCapturingMoves()override;

};


#endif //ROOK_H
