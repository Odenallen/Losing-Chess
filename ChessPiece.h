//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include "ChessMove.h"
#include "ChessBoard.h"

using namespace std;

class ChessPiece {
    friend void ChessBoard::movePiece(ChessMove p);
protected:                               // protected will cause problems
    int m_x, m_y;
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    virtual int validMove(int to_x, int to_y);
public:
    virtual string utfRepresentation();     // may be implemented as string
    virtual char latin1Representation();
    bool m_is_white;
    ChessBoard* m_board;
    // Constructor
    ChessPiece(int x, int y, bool is_white, ChessBoard * board);
    ChessPiece();
    /**
     * Checks if this move is valid for this piece and captures
     * a piece of the opposite color.
     */
    bool capturingMove(int to_x, int to_y);
    /**
     * Checks if this move is valid but does not capture a piece.
     */
    bool nonCapturingMove(int to_x, int to_y);
    virtual vector<ChessMove> capturingMoves();
    virtual vector<ChessMove> nonCapturingMoves();
    vector<int> piecePos();
    void updatePos(int x, int y);

    /**
    * For testing multiple inheritance
    */
    int unnecessary_int;
};


#endif //CHESSPIECE_H