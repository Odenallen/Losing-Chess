//
// DD1388 - Lab 4: Losing Chess
//

#ifndef QUEEN_H
#define QUEEN_H

#include "ChessPiece.h"
#include "Rook.h"
#include "Bishop.h"
class Queen:  public Rook, public Bishop {
    // Override virtual methods from ChessPiece here
// using Rook::Rook;
// using Bishop::Bishop;
public:

    Queen(int x, int y, bool is_white, ChessBoard* board);
    char latin1Representation()override;
    string utfRepresentation()override;
    int validMove(int to_x, int to_y)override;
    vector<ChessMove> capturingMoves()override;
    vector<ChessMove> nonCapturingMoves()override;

};


#endif //QUEEN_H
