//
// DD1388 - Lab 4: Losing Chess
//

#include "King.h"

// Implement method definitions here
string King::utfRepresentation(){
    if (m_is_white){return "\u265A" ;}
    else{return "\u2654";}
}
char King::latin1Representation(){
    if (m_is_white){return 'K';}
    else{return 'k';}
}

vector<ChessMove> King::capturingMoves(){

    /*This functions checks the surrounding cells for possible
    capturing moves and returns this as a vector*/


    vector<ChessMove> moves;

    int x = this->m_x;
    int y = this->m_y;

    for (int i = 0; i < 8; i++){
        int deltax = abs(x - i);
        for (int j = 0; j < 8; j++){

            int deltay = abs(y - j);
            
            // checks if move is valid movement wise
            if (deltax + deltay == 1 || (deltax*deltay == 1)){
                //Valid movement(mathematically speaking)
                if (capturingMove(i,j)){
                    ChessMove okMove;
                    okMove.from_x = x;
                    okMove.from_y = y;
                    okMove.to_x = i;
                    okMove.to_y = j;
                    okMove.piece = this;
                    moves.push_back(okMove);}

                }
            }

        }
    
    return moves;
}

vector<ChessMove> King::nonCapturingMoves(){

vector<ChessMove> moves;

    int x = this->m_x;
    int y = this->m_y;

    for (int i = 0; i < 8; i++){
        int deltax = abs(x - i);
        for (int j = 0; j < 8; j++){

            int deltay = abs(y - j);
            
            // checks if move is valid movement wise
            if (deltax + deltay == 1 || (deltax*deltay == 1)){
                //Valid movement(mathematically speaking)
                if (nonCapturingMove(i,j)){
                    ChessMove okMove;
                    okMove.from_x = x;
                    okMove.from_y = y;
                    okMove.to_x = i;
                    okMove.to_y = j;
                    okMove.piece = this;
                    moves.push_back(okMove);}
                }
            }
        }
    
return moves;

}







int King::validMove(int to_x, int to_y){
    /*
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
   

    
    if (to_x >7 || to_y>7 || to_x < 0 ||to_y < 0){return 0;}
    if (m_board->getcell(to_x,to_y)== nullptr){return 1;}   // nothing in cell, ok move.
    else if (m_board->getcell(to_x,to_y) != nullptr && (m_is_white != m_board->getcell(to_x,to_y)->m_is_white)){return 2;} // occupied but not same team

    else{return 0;   // same team
    }


    // return 0;                                POTENTIAL ISSUE
 }



