//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
    // Override virtual methods from ChessPiece here
    using ChessPiece::ChessPiece;
    char latin1Representation()override;
    string utfRepresentation()override; 
    int validMove(int to_x, int to_y)override;
    vector<ChessMove> capturingMoves()override;
    vector<ChessMove> nonCapturingMoves()override;

};


#endif //KNIGHT_H
