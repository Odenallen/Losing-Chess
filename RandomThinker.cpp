#include "RandomThinker.h"

RandomThinker::RandomThinker(){


}

void RandomThinker::playerMove(ChessBoard & cb){
    // cout << "Player move, is white: "<< is_white << endl;
    vector<ChessMove> capturingMoves = cb.capturingMoves(is_white);
    // cout << "yayay I am lord!\n";
    vector<ChessMove> nonCapturingMoves = cb.nonCapturingMoves(is_white);
    // cout << "Capturing moves: " << capturingMoves.size() << endl;
    // cout << "Non-capturing moves: " << nonCapturingMoves.size() << endl;


    if (capturingMoves.size() == 0 && nonCapturingMoves.size() !=0){    // Non-capturing moves
        int random = rand() % nonCapturingMoves.size();
        // cout <<"nonCapMoves!\n";
        // cout << "Random move pawn promotion:" << nonCapturingMoves[random].pawn_promotion << endl;
        cb.movePiece(nonCapturingMoves[random]);
        if (nonCapturingMoves[random].pawn_promotion){
            // cout << "Pawn promotion" << endl;
            cb.pawnpromotion(nonCapturingMoves[random]);
        }
        // cb.movePiece(nonCapturingMoves[random]);

    }

    else if (capturingMoves.size() != 0){   // Capturing moves
        // cout <<"CapMoves YEEEHAAA!!\n";

        int random = rand() % capturingMoves.size();
        // cout <<"Before: \n" << cb;

        cb.movePiece(capturingMoves[random]);
        // cout <<"After: \n"<< cb;
        cout <<"\n---------------------\n";
        if (capturingMoves[random].pawn_promotion){
            // cout << "Pawn promotion" << endl;
            cb.pawnpromotion(capturingMoves[random]);
        }
        // cb.movePiece(capturingMoves[random]);
    }

    else{
        cout << "No moves available" << endl;
    

    }}


