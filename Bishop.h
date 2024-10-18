//
// DD1388 - Lab 4: Losing Chess
//

#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

class Bishop : virtual public ChessPiece {
    // Override virtual methods from ChessPiece here
    public:
    
    using ChessPiece::ChessPiece;
    char latin1Representation()override;
    string utfRepresentation()override; 
    int validMove(int to_x, int to_y)override;
    // int pathMove(int to_x, int to_y,int deltaX,int deltaY);
    vector<ChessMove> capturingMoves()override;
    vector<ChessMove> nonCapturingMoves()override;



};


#endif //BISHOP_H
