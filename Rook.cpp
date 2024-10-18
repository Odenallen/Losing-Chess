//
// DD1388 - Lab 4: Losing Chess
//

#include "Rook.h"

// Implement method definitions here
string Rook::utfRepresentation(){
    if (m_is_white){return "\u265C";}
    else{return "\u2656";}
}
char Rook::latin1Representation(){
    if (m_is_white){return 'R';}
    else{return 'r';}
}
int Rook::validMove(int to_x, int to_y){
    
    /*
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */


    if (to_x >7 || to_y>7 || to_x < 0 ||to_y < 0){return 0;}
    if (m_board->getcell(to_x,to_y)== nullptr){return 1;}   // nothing in cell, ok move.
    else if (m_board->getcell(to_x,to_y) != nullptr && (m_is_white != m_board->getcell(to_x,to_y)->m_is_white)){ /*cout << " Cap move" << endl;*/ return 2;} // occupied but not same team

    else{
         return 0;   // same team
    }
  
}

vector<ChessMove> Rook::capturingMoves(){

    vector<ChessMove> move;
    int x = this->m_x;
    int y = this->m_y;

    int jump = x + 1;

    if (jump < 8){

        while ((m_board->getcell(jump,y) == nullptr)){
            jump++;
            if (jump > 7){
                break;
                }
            }

        if (capturingMove(jump, y)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = jump;
            okMove.to_y = y;
            okMove.piece = this;
            move.push_back(okMove);
            }
        }

    jump = x - 1;

    if (jump >= 0){
        while ((m_board->getcell(jump,y) == nullptr)){
            jump--;
            if (jump < 0){
                break;
                }
            }
        if (capturingMove(jump, y)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = jump;
            okMove.to_y = y;
            okMove.piece = this;
            move.push_back(okMove);
            }
        }
    

    jump = y + 1;
    
    if (jump < 8){
        while ((m_board->getcell(x,jump) == nullptr)){
            jump++;
            if (jump > 7){
                break;
                }
            }
        if (capturingMove(x, jump)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = x;
            okMove.to_y = jump;
            okMove.piece = this;
            move.push_back(okMove);
            }
        }

    jump = y - 1;

    if (jump >= 0){
        while ((m_board->getcell(x,jump) == nullptr)){
            jump--;
            if (jump < 0){
                break;
                }
            }
        if (capturingMove(x, jump)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = x;
            okMove.to_y = jump;
            okMove.piece = this;
            move.push_back(okMove);
            }
        }
    
    return move;
    }


vector<ChessMove> Rook::nonCapturingMoves(){

    vector<ChessMove> move;
    int x = this->m_x;
    int y = this->m_y;
    int jump = x + 1;

    if (jump < 8){

        while ((m_board->getcell(jump,y) == nullptr)){

            if (nonCapturingMove(jump, y)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = jump;
                okMove.to_y = y;
                okMove.piece = this;
                move.push_back(okMove);
                }

            jump++;
            if (jump > 7){
                break;
                }
            }
        }

    jump = x - 1;
    
    if (jump >= 0){
        while ((m_board->getcell(jump,y) == nullptr)){
            
            if (nonCapturingMove(jump, y)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = jump;
                okMove.to_y = y;
                okMove.piece = this;
                move.push_back(okMove);
                }
            jump--;
            if (jump < 0){
                break;
                }
            }
        }
    

    jump = y + 1;
    
    if (jump < 8){
        while ((m_board->getcell(x,jump) == nullptr)){
            if (nonCapturingMove(x, jump)){
               ChessMove okMove;
               okMove.from_x = x;
               okMove.from_y = y;
               okMove.to_x = x;
               okMove.to_y = jump;
               okMove.piece = this;
               move.push_back(okMove);
                }
            jump++;
            if (jump > 7){
                break;
                }
            }
        
        }

    jump = y - 1;
    
    if (jump >= 0){
        while ((m_board->getcell(x,jump) == nullptr)){
            if (nonCapturingMove(x, jump)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = x;
                okMove.to_y = jump;
                okMove.piece = this;
                move.push_back(okMove);
                }
            jump--;
            if (jump < 0){
                break;
                }
            }
        
        }

    return move;
    }
