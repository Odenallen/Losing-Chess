//
// DD1388 - Lab 4: Losing Chess
//

#ifndef KING_H
#define KING_H

#include "ChessPiece.h"


class King : public ChessPiece {
    // Override virtual methods from ChessPiece here
    using ChessPiece::ChessPiece;
    virtual char latin1Representation()override;
    virtual string utfRepresentation()override; 
    virtual int validMove(int to_x, int to_y)override;
    virtual vector<ChessMove> capturingMoves()override;
    virtual vector<ChessMove> nonCapturingMoves()override;

    
};


#endif //KING_H
