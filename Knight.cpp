//
// DD1388 - Lab 4: Losing Chess
//

#include "Knight.h"

// Implement method definitions here
string Knight::utfRepresentation(){
    if (m_is_white){return "\u265E" ;}
    else{return "\u2658";}
}
char Knight::latin1Representation(){
    if (m_is_white){return 'N';}
    else{return 'n';}
}
int Knight::validMove(int to_x, int to_y){
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    if (to_x >7 || to_y>7 || to_x < 0 ||to_y < 0){ return 0;   }
    if (m_board->getcell(to_x,to_y)== nullptr){  return 1;   }   // nothing in cell, ok move.

    else if (m_board->getcell(to_x,to_y) != nullptr && (m_is_white != m_board->getcell(to_x,to_y)->m_is_white)){  return 2;} // occupied but not same team

    else{
         return 0;   // same team
    }
}


vector<ChessMove> Knight::capturingMoves(){

    vector<ChessMove> moves;
    // cout << "Made it into Knight CapturingMoves()!" << endl;
    int x = this->m_x;
    int y = this->m_y;
    int deltax = 0;
    int deltay = 0;
    
    for (int i = 0 ; i < 8; i++){
        deltax = abs(x - i);

        for (int j = 0; j < 8; j++){
            deltay = abs(y - j);
            if (deltax*deltax + deltay*deltay == 5){
                if (capturingMove(i,j)){

                    ChessMove okMove;
                    okMove.from_x = this->m_x;
                    okMove.from_y = this->m_y;
                    okMove.to_x = i;
                    okMove.to_y = j;
                    okMove.piece = this;
                    moves.push_back(okMove);
                }
            }
            
        }
    }

    return moves;

}

vector<ChessMove> Knight::nonCapturingMoves(){
    vector<ChessMove> moves;
    int x = this->m_x;
    int y = this->m_y;
    int deltax = 0;
    int deltay = 0;
    
    for (int i = 0 ; i < 8; i++){
        deltax = abs(x - i);

        for (int j = 0; j < 8; j++){
            deltay = abs(y - j);
            if (deltax*deltax + deltay*deltay == 5){
                if (nonCapturingMove(i,j)){
                    
                    ChessMove okMove;
                    okMove.from_x = this->m_x;
                    okMove.from_y = this->m_y;
                    okMove.to_x = i;
                    okMove.to_y = j;
                    okMove.piece = this;
                    moves.push_back(okMove);
                }
            }
            
        }
    }

    return moves;
}

