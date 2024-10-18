//
// DD1388 - Lab 4: Losing Chess
//

#include "Bishop.h"

// Implement method definitions here
string Bishop::utfRepresentation(){
    if (m_is_white){return "\u265D";}
    else{return "\u2657";}
}
char Bishop::latin1Representation(){
    if (m_is_white){return 'B';}
    else{return 'b';}
}
int Bishop::validMove(int to_x, int to_y){
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    // cout << "Validmove Bishop" << endl;

    if (to_x >7 || to_y>7 || to_x < 0 ||to_y < 0){  /*cout << to_x << ',' << to_y << endl ;*/ return 0;   }

    if (m_board->getcell(to_x,to_y)== nullptr){   return 1;   }   // nothing in cell, ok move.


    else if (m_board->getcell(to_x,to_y) != nullptr && (m_is_white != m_board->getcell(to_x,to_y)->m_is_white)){ /*cout << " Cap move" << endl;*/ return 2;} // occupied but not same team

    else{

         return 0;   // same team




    }
    
   
}

vector<ChessMove> Bishop::capturingMoves(){

    vector<ChessMove> moves;
    int x = this->m_x;
    int y = this->m_y;

    int jumpx = 1 + x;
    int jumpy = 1 + y;

    if ( jumpx < 8 && jumpy < 8){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            jumpx++;
            jumpy++;
            if (jumpx == 8 || jumpy == 8){
                break;
            }
        }

        if (capturingMove(jumpx,jumpy)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = jumpx;
            okMove.to_y = jumpy;
            okMove.piece = this;
            moves.push_back(okMove);
        }
    }


    jumpx = -1 + x;
    jumpy = -1 + y;

    if ( jumpx > -1 && jumpy > -1){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            jumpx--;
            jumpy--;
            if (jumpx == -1 || jumpy == -1){
                break;
            }
        }

        if (capturingMove(jumpx,jumpy)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = jumpx;
            okMove.to_y = jumpy;
            okMove.piece = this;
            moves.push_back(okMove);
        }
    }


    jumpx = 1 + x;
    jumpy = -1 + y;

    if ( jumpx < 8 && jumpy > -1){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            jumpx++;
            jumpy--;
            if (jumpx == 8 || jumpy == -1){
                break;
            }
        }

        if (capturingMove(jumpx,jumpy)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = jumpx;
            okMove.to_y = jumpy;
            okMove.piece = this;
            moves.push_back(okMove);
        }
    }



    jumpx = -1 + x;
    jumpy = 1 + y;

    if ( jumpx > -1 && jumpy < 8){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            jumpx--;
            jumpy++;
            if (jumpx == -1 || jumpy == 8){
                break;
            }
        }

        if (capturingMove(jumpx,jumpy)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = jumpx;
            okMove.to_y = jumpy;
            okMove.piece = this;
            moves.push_back(okMove);
        }
    }

    return moves;


    }


vector<ChessMove> Bishop::nonCapturingMoves(){
    vector<ChessMove> moves;
    int x = this->m_x;
    int y = this->m_y;

    int jumpx = 1 + x;
    int jumpy = 1 + y;

    if ( jumpx < 8 && jumpy < 8){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            if (nonCapturingMove(jumpx,jumpy)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = jumpx;
                okMove.to_y = jumpy;
                okMove.piece = this;
                moves.push_back(okMove);
            }
            jumpx++;
            jumpy++;
            if (jumpx == 8 || jumpy == 8){
                break;
            }
        }
        }

    jumpx = -1 + x;
    jumpy = -1 + y;

    if ( jumpx > -1 && jumpy > -1){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            if (nonCapturingMove(jumpx,jumpy)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = jumpx;
                okMove.to_y = jumpy;
                okMove.piece = this;
                moves.push_back(okMove);
            }
            jumpx--;
            jumpy--;
            if (jumpx == -1 || jumpy == -1){
                break;
            }
        }}


    jumpx = 1 + x;
    jumpy = -1 + y;

    if ( jumpx < 8 && jumpy > -1){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            if (nonCapturingMove(jumpx,jumpy)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = jumpx;
                okMove.to_y = jumpy;
                okMove.piece = this;
                moves.push_back(okMove);
            }
            jumpx++;
            jumpy--;
            if (jumpx == 8 || jumpy == -1){
                break;
            }
        }}

    jumpx = -1 + x;
    jumpy = 1 + y;

    if ( jumpx > -1 && jumpy < 8){
        while (m_board->getcell(jumpx,jumpy) == nullptr){
            if (nonCapturingMove(jumpx,jumpy)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = jumpx;
                okMove.to_y = jumpy;
                okMove.piece = this;
                moves.push_back(okMove);
            }
            jumpx--;
            jumpy++;
            if (jumpx == -1 || jumpy == 8){
                break;
            }
        }}

    return moves;
}