#include "OnestepAhead.h"

void OneStepAhead::playerMove(ChessBoard & cb){
    // cout << "we are: " << is_white << endl;
    vector<ChessMove> capturingMoves = cb.capturingMoves(is_white);
    vector<ChessMove> nonCapturingMoves = cb.nonCapturingMoves(is_white);
    vector<ChessMove> opponentCapturingMoves = cb.capturingMoves(!is_white);
    vector<ChessMove> opponentNonCapturingMoves = cb.nonCapturingMoves(!is_white);


    bool OppCapture = false;
    // int oppElement = 0;
    bool pawnpromExists = false;

    if (capturingMoves.size() > 0){
        // cout <<"not here"<<endl;
        // cout <<capturingMoves.size()<<endl;


        for (int i =0 ; i < capturingMoves.size() ; i++ ){
        
            auto orgcb = cb;

            cb.movePiece(capturingMoves[i]);
            
            auto oppNextMoves = cb.capturingMoves(!is_white);
            for (int j = 0; j < oppNextMoves.size(); j++){
                if (oppNextMoves[j].to_x == capturingMoves[i].to_x && oppNextMoves[j].to_y == capturingMoves[i].to_y){
                    OppCapture = true;
                    break;
                }
                
            }
            if (OppCapture){
                if (capturingMoves[i].pawn_promotion){
                cb.smartPawnPromotion(capturingMoves[i]);
            }

                break;}
            else if (!OppCapture){

                cb = cb.copyBoard(capturingMoves[i],orgcb);
                orgcb.deleteBoard();

        }
        }
        if (!OppCapture){
            // cout << "No capture for opponent, making a random move" << endl;
            int random = rand() % capturingMoves.size();
            
            
            cb.movePiece(capturingMoves[random]);
            if (capturingMoves[random].pawn_promotion){
                cb.smartPawnPromotion(capturingMoves[random]);
                return;
            }
        }
    }


    else if (capturingMoves.size() == 0 && nonCapturingMoves.size() > 0){   
        // cout << "we should be here!"<<endl;
        for (int i =0 ; i < nonCapturingMoves.size() ; i++ ){

            auto orgcb = cb;
            cb.movePiece(nonCapturingMoves[i]);
            auto oppNextMoves = cb.capturingMoves(!is_white);
            for (int j = 0; j < oppNextMoves.size(); j++){
                if (oppNextMoves[j].to_x == nonCapturingMoves[i].to_x && oppNextMoves[j].to_y == nonCapturingMoves[i].to_y){
                    OppCapture = true;
                    break;
                }
                
            }
            if (OppCapture){
                // opponent will capture!                
                if (nonCapturingMoves[i].pawn_promotion){
                    cb.smartPawnPromotion(nonCapturingMoves[i]);
                return;
            }
                
                break;}
            else if (!OppCapture){
                // cout <<"here!"<<endl;
                cb = cb.copyBoard(nonCapturingMoves[i],orgcb);
                orgcb.deleteBoard();
            }


    }

    if (!OppCapture){
        // cout << "No capture for opponent, making a random move" << endl;
        //Random move
        int random = rand() % nonCapturingMoves.size();
        
        cb.movePiece(nonCapturingMoves[random]);
        // cout <<"Pawnprom Status: "<< nonCapturingMoves[random].pawn_promotion << endl;
        if (nonCapturingMoves[random].pawn_promotion){
            // cout <<" inside!"<<endl;
            cb.smartPawnPromotion(nonCapturingMoves[random]);
        }
    }
    }
    else{return;}

}


