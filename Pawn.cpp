//
// DD1388 - Lab 4: Losing Chess
//

#include "Pawn.h"

// Implement method definitions here

string Pawn::utfRepresentation(){
    if (m_is_white){return "\u265F";}
    else{return "\u2659";}
}
char Pawn::latin1Representation(){
    if (m_is_white){return 'P';}
    else{return 'p';}
}
int Pawn::validMove(int to_x, int to_y){
    /**
     * Returns 0 if target square is unreachable.
     * Returns 1 if target square is reachable and empty.
     * Returns 2 if move captures a piece.
     */
    
    if (to_x >7 || to_y>7 || to_x < 0 ||to_y < 0){  /*cout << to_x << ',' << to_y << endl ;*/ return 0;   }
    if (m_board->getcell(to_x,to_y)== nullptr){ /*cout << "returned 1"<< endl;*/   return 1;   }   // nothing in cell, ok move.
    else if (m_board->getcell(to_x,to_y) != nullptr && (m_is_white != m_board->getcell(to_x,to_y)->m_is_white)){ return 2;} // occupied but not same team

    else{return 0;   // same team
    }
    
    
    // return 0;                       
    
    
    }

    vector<ChessMove> Pawn::capturingMoves(){

        vector<ChessMove> moves;

        int x = this->m_x;
        int y = this->m_y;
        if (m_is_white){
            
            if (capturingMove(x-1,y-1)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = x-1;
                okMove.to_y = y-1;
                if (y == 1){
                    okMove.pawn_promotion = true;
                }
                okMove.piece = this;
                moves.push_back(okMove);
                
                
            }

            if (capturingMove(x+1,y-1)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = x+1;
                okMove.to_y = y-1;
                if (y == 1){
                    okMove.pawn_promotion = true;
                }
                okMove.piece = this;
                moves.push_back(okMove);
                
                
            }


        }
        else{
            if (capturingMove(x-1,y+1)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = x-1;
                okMove.to_y = y+1;
                if (y+1 == 7){
                    okMove.pawn_promotion = true;
                }
                okMove.piece = this;
                moves.push_back(okMove);

                
        }
            if (capturingMove(x+1,y+1)){
                ChessMove okMove;
                okMove.from_x = x;
                okMove.from_y = y;
                okMove.to_x = x+1;
                okMove.to_y = y+1;
                if (y+1 == 7){
                    okMove.pawn_promotion = true;
                }
                okMove.piece = this;
                moves.push_back(okMove);

                
                
            }
        }

        return moves;

    }

vector<ChessMove> Pawn::nonCapturingMoves(){
    vector<ChessMove> moves;

    int x = this->m_x;
    int y = this->m_y;
    if (m_is_white){
        if (y == 6){
            if (nonCapturingMove(x,y-1)){
                if (nonCapturingMove(x,y-2)){
                    ChessMove okMove;
                    okMove.from_x = x;
                    okMove.from_y = y;
                    okMove.to_x = x;
                    okMove.to_y = y-2;
                    okMove.piece = this;
                    moves.push_back(okMove);

                    }
                }
            }
            
        if (nonCapturingMove(x,y-1)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = x;
            okMove.to_y = y-1;
            // if (y-1 == 0){
            if (y == 1){
                okMove.pawn_promotion = true;
                }
            okMove.piece = this;
            moves.push_back(okMove);
            
            }

        }
    else{

        if (y==1){
            if(nonCapturingMove(x,y+1)){
                if (nonCapturingMove(x,y+2)){
                    ChessMove okMove;
                    okMove.from_x = x;
                    okMove.from_y = y;
                    okMove.to_x = x;
                    okMove.to_y = y+2;
                    okMove.piece = this;
                    moves.push_back(okMove);
                    }
                }
            }


        if (nonCapturingMove(x,y+1)){
            ChessMove okMove;
            okMove.from_x = x;
            okMove.from_y = y;
            okMove.to_x = x;
            okMove.to_y = y+1;
            if (y+1 == 7){
                okMove.pawn_promotion = true;
                }
            okMove.piece = this;
            moves.push_back(okMove);

            }
        }

    return moves;
    }