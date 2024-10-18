//
// DD1388 - Lab 4: Losing Chess
//

#include "Queen.h"
Queen::Queen(int x, int y, bool is_white, ChessBoard* board){
Rook::m_x = x;
Rook::m_y = y;
Rook::m_is_white = is_white;
Rook::m_board = board;
Bishop::m_x = x;
Bishop::m_y = y;
Bishop::m_is_white = is_white;
Bishop::m_board = board;


}
char Queen::latin1Representation(){
    if (m_is_white){return 'Q';}
    else{return 'q';}
}

string Queen::utfRepresentation(){
    if (m_is_white){return "\u265B" ;}
    else{return "\u2655";}


}
 int Queen::validMove(int to_x, int to_y){
 
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    
   if (to_x >7 || to_y>7 || to_x < 0 ||to_y < 0){return 0;}
    if (m_board->getcell(to_x,to_y)== nullptr){   return 1;   }   // nothing in cell, ok move.
    else if (m_board->getcell(to_x,to_y) != nullptr && (m_is_white != m_board->getcell(to_x,to_y)->m_is_white)){return 2;} // occupied but not same team

    else{return 0;   // same team
    }
 
 
 
 return 0;}

vector<ChessMove> Queen::capturingMoves(){
    vector<ChessMove> moves;
    vector<ChessMove> movesBishop = this->Bishop::capturingMoves();
    vector<ChessMove> movesRook = this->Rook::capturingMoves();
    moves.insert(moves.end(),movesBishop.begin(),movesBishop.end());
    moves.insert(moves.end(),movesRook.begin(),movesRook.end());

    return moves;
}

vector<ChessMove> Queen::nonCapturingMoves(){
    vector<ChessMove> moves;
    vector<ChessMove> movesBishop = this->Bishop::nonCapturingMoves();
    vector<ChessMove> movesRook = this->Rook::nonCapturingMoves();
    moves.insert(moves.end(),movesBishop.begin(),movesBishop.end());
    moves.insert(moves.end(),movesRook.begin(),movesRook.end());

    return moves;
}
