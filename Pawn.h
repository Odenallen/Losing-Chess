//
// DD1388 - Lab 4: Losing Chess
//

#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

class Pawn : public ChessPiece {
    // Override virtual methods from ChessPiece here
    
    using ChessPiece::ChessPiece;
    char latin1Representation()override;
    string utfRepresentation()override; 
    int validMove(int to_x, int to_y)override;
    vector<ChessMove> capturingMoves()override;
    vector<ChessMove> nonCapturingMoves()override;





};


#endif //PAWN_H
