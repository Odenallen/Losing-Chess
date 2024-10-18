//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
#include <typeinfo>
#include <algorithm>

using namespace std;

void ChessBoard::movePiece(ChessMove chess_move) {
    // Implementation goes here

       bool non_capture = false;
       auto temp = m_state(chess_move.from_y,chess_move.from_x);
       bool found = false;
        
       if (m_state(chess_move.to_y,chess_move.to_x) != nullptr){    //capturing move.
        

            if (chess_move.piece->m_is_white){
                for (auto i = 0; i < m_black_pieces.size(); i++){
                    if (m_black_pieces[i] == nullptr){
                        continue;
                    }
                    else if (m_black_pieces[i]->m_x == chess_move.to_x && m_black_pieces[i]->m_y == chess_move.to_y){
                        
                        found = true;
                        m_black_pieces[i] = nullptr;
                        m_state(chess_move.to_y,chess_move.to_x) = nullptr;
                        
                    }

                }

                if (!found){
                    // cout << m_state(chess_move.to_y,chess_move.to_x)->latin1Representation() << endl;
                }

             }

            else{
                for (auto i = 0; i < m_white_pieces.size(); i++){
                    
                    if (m_white_pieces[i] == nullptr){
                        continue;
                    }
                
                    else if (m_white_pieces[i]->m_x == chess_move.to_x && m_white_pieces[i]->m_y == chess_move.to_y){
                        m_white_pieces[i] = nullptr;
                        m_state(chess_move.to_y,chess_move.to_x) = nullptr; // 
                        found = true;


                    }
                   
                }

                if (!found){
                    // cout << "No piece to capture\n";
                    // cout << m_state(chess_move.to_y,chess_move.to_x)->latin1Representation() << endl;
                }
            }
        }

        else{
            non_capture = true;
        }
        
        if (chess_move.piece->m_is_white){
            for (auto i = 0; i < m_white_pieces.size(); i++){
                if (m_white_pieces[i] != nullptr){
                    vector<int> position = m_white_pieces[i]->piecePos();

                    if (position[0] == chess_move.from_x && position[1] == chess_move.from_y){
                        m_white_pieces[i]->m_x = chess_move.to_x;
                        m_white_pieces[i]->m_y = chess_move.to_y;
                        removePiece(chess_move.from_x,chess_move.from_y);
                        m_state(chess_move.to_y,chess_move.to_x) = temp;

                    }
                }
            }
        }

        else{

            for (auto i = 0; i < m_black_pieces.size(); i++){
                if (m_black_pieces[i] != nullptr){
                    vector<int> position = m_black_pieces[i]->piecePos();

                    if (position[0] == chess_move.from_x && position[1] == chess_move.from_y){

                        m_black_pieces[i]->m_x = chess_move.to_x;
                        m_black_pieces[i]->m_y = chess_move.to_y;
                        removePiece(chess_move.from_x,chess_move.from_y);
                        m_state(chess_move.to_y,chess_move.to_x) = temp;
                
                    }
                }
                
            }
        }


}

void ChessBoard::printPieces(){

    for (int k = 0 ; k < 8; k++){
        for (int l = 0; l < 8; l++){
            auto t2 = getcell(k,l).get();
            if (t2 != nullptr){
            cout << t2->latin1Representation() << " y,x: " << k << "," << l <<endl;
            cout << "\n\n  ";}
        }
    }

}


vector<ChessMove> ChessBoard::capturingMoves(bool is_white) {
    vector<ChessMove> retVec;
    if (is_white){
        for (int i = 0; i<m_white_pieces.size(); i++){
            if (m_white_pieces[i] != nullptr){
                vector<ChessMove> whiteMoves = m_white_pieces[i]->capturingMoves();
                retVec.insert(retVec.end(),whiteMoves.begin(),whiteMoves.end());
            }
        }
    }

    else {
        for (int i = 0; i<m_black_pieces.size(); i++){
            if (m_black_pieces[i] != nullptr){
            vector<ChessMove> blackMoves = m_black_pieces[i]->capturingMoves();
            retVec.insert(retVec.end(),blackMoves.begin(),blackMoves.end());
            }
        }
    }

    return retVec;
}


vector<ChessMove> ChessBoard::nonCapturingMoves(bool is_white) {
    vector<ChessMove> retVec;

    if (is_white){
    
        for (int i = 0; i<m_white_pieces.size(); i++){
            if (m_white_pieces[i] != nullptr){
                vector<ChessMove> whiteMoves = m_white_pieces[i]->nonCapturingMoves();
                retVec.insert(retVec.end(),whiteMoves.begin(),whiteMoves.end());
            }
        }
    }
    else {

        for (int i = 0; i<m_black_pieces.size(); i++){
            if (m_black_pieces[i] != nullptr){
                vector<ChessMove> blackMoves = m_black_pieces[i]->nonCapturingMoves();
                retVec.insert(retVec.end(),blackMoves.begin(),blackMoves.end());
            }
        }

    }
    return retVec;
}



ChessBoard & operator>>(istream & is, ChessBoard & cb) {
    string line="";
    cb.boardSetup();

    is >> line; 

    if (line.size() != 64){                         // Handle input with \n unlike test cases give!
        for (int i = 0; i < 7; i++){
            string temp;
            is >> temp;
            line += temp;
        }
        
    }
    int y = 0;
    for (int i = 0; i < 8; i++){
        for (int x = 0; x < 8; x++){
            if (line[i*8+x] != '.'){
                cb.createPiece(line[i*8+x],x,y);
            
            }
            if ((8-1)+8*i == i*8+x){
                y +=1;

            }
        }
    }

    return cb;
}

ChessBoard & operator<<(ostream & os, ChessBoard & cb) {
    auto board = cb.getBoard();

    for (int i = 0; i < board.rows(); i++){
        for (int j = 0; j < board.cols(); j++){
            if (board(i,j) == nullptr){
                cout << '.';
            }
            else{
                cout << board(i,j).get()->utfRepresentation();
                // cout << board(i,j).get()->latin1Representation();

            }
        }
        cout << endl;
    }
    // cout <<"white pieces:\n";
    // cout  << cb.m_white_pieces.size() <<endl;
    // for(int i =0; i < cb.m_white_pieces.size() ; i++ ){
    //     if (cb.m_white_pieces[i]!= nullptr){
    //         cout << cb.m_white_pieces[i]->latin1Representation()<<endl;           

    //     }
    // }
    // cout <<"Black pieces; \n";
    // cout << cb.m_black_pieces.size() <<endl;
    // int temp2 = 0;
    // for (int j = 0 ; j < cb.m_black_pieces.size() ; j++){
    //     // cout <<" j :" << j <<endl;
    //     if (cb.m_black_pieces[j]!= nullptr){
    //         cout << cb.m_black_pieces[j]->latin1Representation()<<endl;
    //         temp2++;
    //     }

    // }
    // cout <<"temp2: " << temp2 << endl;
    return cb;
}


Matrix<shared_ptr<ChessPiece>> & ChessBoard::getBoard(){
    return m_state;
}

void ChessBoard::createPiece(char piece, int x, int y){

    if(isupper(piece)){ // White.
        if (piece == 'K'){//    King

            shared_ptr<ChessPiece> a_King = make_shared<King>(x,y,1,this);
            m_state(y,x) = a_King;
            m_white_pieces.push_back(a_King.get());
            
        }
        if (piece == 'R'){//    Rook
            shared_ptr<ChessPiece> a_Rook = make_shared<Rook>(x,y,1,this);
            m_state(y,x) = a_Rook;
            m_white_pieces.push_back(a_Rook.get());
        }
        if (piece == 'B'){//    Bishop
            // cout << "B-ishop @ : "<< y<<',' << x << endl;
            shared_ptr<ChessPiece> a_Bishop = make_shared<Bishop>(x,y,1,this);
            m_state(y,x) = a_Bishop;
            m_white_pieces.push_back(a_Bishop.get());
        }
        if (piece == 'Q'){//    Queen
            // cout << "Q-ueen @ : "<< y<<',' << x << endl;
            shared_ptr<ChessPiece> a_Queen = make_shared<Queen>(x,y,1,this);
            m_state(y,x) = a_Queen;
            m_white_pieces.push_back(a_Queen.get());
        }
        if (piece == 'N'){//    kNight
            // cout << "N-ight @ : "<< y<<',' << x << endl;
            shared_ptr<ChessPiece> a_Knight = make_shared<Knight>(x,y,1,this);
            m_state(y,x) = a_Knight;
            m_white_pieces.push_back(a_Knight.get());
        }

        if (piece == 'P'){//    Pawn
            // cout << "P-awn @ : "<< y<<',' << x << endl;
            shared_ptr<ChessPiece> a_Pawn = make_shared<Pawn>(x,y,1,this);
            m_state(y,x) = a_Pawn;
            m_white_pieces.push_back(a_Pawn.get());
        }

    } 


    if(islower(piece)){
        if (piece =='k'){
            shared_ptr<ChessPiece> a_king = make_shared<King>(x,y,0,this);
            m_state(y,x) = a_king;
            m_black_pieces.push_back(a_king.get());
        }

        if (piece =='r'){
            // cout<<"rook"<< endl;

            shared_ptr<ChessPiece> a_rook = make_shared<Rook>(x,y,0,this);
            m_state(y,x) = a_rook;
            m_black_pieces.push_back(a_rook.get());
        }
        if (piece =='b'){
            // cout << "b-ishop @: " << y<<',' << x << endl;
            shared_ptr<ChessPiece> a_bishop = make_shared<Bishop>(x,y,0,this);
            m_state(y,x) = a_bishop;
            m_black_pieces.push_back(a_bishop.get());
        }
        if (piece =='q'){
            // cout << "q-ueen @: " << y<<',' << x << endl;
            shared_ptr<ChessPiece> a_queen = make_shared<Queen>(x,y,0,this);
            m_state(y,x) = a_queen;
            m_black_pieces.push_back(a_queen.get()); 

        } 

        if (piece =='n'){
            // cout << "n-ight @: " << y<<',' << x << endl;
            shared_ptr<ChessPiece> a_knight = make_shared<Knight>(x,y,0,this);
            m_state(y,x) = a_knight;
            m_black_pieces.push_back(a_knight.get());
        }

        if (piece =='p'){
            // cout << "p-awn @: " << y<<',' << x << endl;
            shared_ptr<ChessPiece> a_pawn = make_shared<Pawn>(x,y,0,this);
            m_state(y,x) = a_pawn;
            m_black_pieces.push_back(a_pawn.get());
        }
    }

}



bool ChessBoard::gameover(){
    int blackPieces = m_black_pieces.size();
    int whitePieces = m_white_pieces.size();
    int incrementor = 0;

    for (auto i = 0; i < m_white_pieces.size(); i++){
        if (m_white_pieces[i] == nullptr){
            incrementor += 1;
        }
    }
    if (incrementor == whitePieces){
    // cout << "incrementor: " << incrementor << endl;
        return true;
    }
    incrementor = 0;
    for (auto i = 0; i < m_black_pieces.size(); i++){
        if (m_black_pieces[i] == nullptr){
            incrementor += 1;
        }
    }
    if (incrementor == blackPieces){
    // cout << "incrementor: " << incrementor << endl;
        return true;
    }
    return false;
}

void ChessBoard::pawnpromotion(ChessMove chess_move){
    int indexPromotion;
    int random = rand() % 3;

    if (chess_move.piece->m_is_white){
        for (auto i = 0; i < m_white_pieces.size(); i++){
            if (m_white_pieces[i] == chess_move.piece){
                m_white_pieces[i] = nullptr;
                // cout << "len white pieces before: "<< m_white_pieces.size() << endl;
                m_white_pieces.erase(m_white_pieces.begin() + i);
                // cout << "len white pieces After: "<< m_white_pieces.size() << endl;

                removePiece(chess_move.from_x,chess_move.from_y);
                indexPromotion = i;
            }
        }


        array<char,4> promotionPiecesWhite = {'Q','R','B','N'};
        createPiece(promotionPiecesWhite[random],chess_move.to_x,chess_move.to_y);
    


    }

    else{
        for (auto i = 0; i < m_black_pieces.size(); i++){
            if (m_black_pieces[i] == chess_move.piece){
                m_black_pieces[i] = nullptr;
                // cout << "len black pieces before: "<< m_black_pieces.size() << endl;
                m_black_pieces.erase(m_black_pieces.begin() + i);
                // cout << "len black pieces before: "<< m_black_pieces.size() << endl;

                removePiece(chess_move.from_x,chess_move.from_y);
                indexPromotion = i;
            }
        }

        array<char,4> promotionPiecesBlack = {'q','r','b','n'};
        createPiece(promotionPiecesBlack[random],chess_move.to_x,chess_move.to_y);
    }
}


void ChessBoard::smartPawnPromotion(ChessMove chess_move){
        // cout << "SmartPawnProm" << endl;
        array<char,4> promotionPiecesWhite = {'Q','R','B','N'};
        array<char,4> promotionPiecesBlack = {'q','r','b','n'};
        // cout << "we are: "<< chess_move.piece->m_is_white << endl;

        if (chess_move.piece->m_is_white){
            // cout <<"white\n";
            for (int i = 0 ; i < m_white_pieces.size(); i++){
                if (m_white_pieces[i] != nullptr){
                    vector<int> pos = m_white_pieces[i]->piecePos();
                    if (pos[0] == chess_move.to_x && pos[1]==chess_move.to_y){

                        // cout << "found piece\n";
                        m_white_pieces[i] = nullptr;
                        m_white_pieces.erase(m_white_pieces.begin() + i);           // ADDED THIS !!
                        removePiece(chess_move.from_x,chess_move.from_y);
                        bool can_capture = false;
                        for (int j = 0 ; j < promotionPiecesWhite.size(); j++){
                            can_capture = false;
                            createPiece(promotionPiecesWhite[j],chess_move.to_x,chess_move.to_y);
                            auto nextMoves = capturingMoves(chess_move.piece->m_is_white);
                            
                            for(int k = 0; k < nextMoves.size(); k++){
                                if (nextMoves[k].from_x == chess_move.to_x && nextMoves[k].from_y == chess_move.to_y){
                                    can_capture = true;
                                    // cout << "Can capture\n";
                                    // cout <<"Could not choose: " << promotionPiecesWhite[j] << endl;
                                    // cout << "from: " << nextMoves[k].from_y << ',' << nextMoves[k].from_x << endl;
                                    // cout << "to: " << nextMoves[k].to_y << ',' << nextMoves[k].to_x << endl;
                                    // cout << "Length before pop: " << m_white_pieces.size() << endl;
                                    m_white_pieces.back() = nullptr;
                                    m_white_pieces.pop_back();
                                    // cout << "Length after pop: " << m_white_pieces.size() << endl;
                                    // cout << "\n"<<endl;

                                    removePiece(chess_move.to_x,chess_move.to_y);
                                    break;
                                }   }

                        if (!can_capture){
                            // cout << "Can not capture, Success\n";
                            // cout << "Chose: " << promotionPiecesWhite[j] << endl;
                            // cout << "new board\n" << *this;
                            return;
                        }
    
                        }
                        if (can_capture){
                            // cout << "No piece that does not capture\nDo random promotion" << endl;
                            int random = rand() % 4;
                            createPiece(promotionPiecesWhite[random],chess_move.to_x,chess_move.to_y);
                            return;
                        }
                    }
                }
            }   
        }

        else{
            // cout <<"black"<< endl;

            // iterate through all black pieces and current piece
            for (int i = 0 ; i < m_black_pieces.size(); i++){
                if (m_black_pieces[i] != nullptr){
                    vector<int> pos = m_black_pieces[i]->piecePos();
                    if (pos[0] == chess_move.to_x && pos[1]==chess_move.to_y){

                        m_black_pieces[i] = nullptr;
                        m_black_pieces.erase(m_black_pieces.begin() + i);                   // ADDED THIS!!!
                        removePiece(chess_move.from_x,chess_move.from_y);
                        bool can_capture = false;
                        // cout << "black? "<<chess_move.piece->m_is_white <<endl;

                        for (int j = 0 ; j < promotionPiecesBlack.size(); j++){
                            can_capture = false;
                            createPiece(promotionPiecesBlack[j],chess_move.to_x,chess_move.to_y);

                            // auto nextMoves = capturingMoves(!chess_move.piece->m_is_white);
                            auto nextMoves = capturingMoves(chess_move.piece->m_is_white);

                            for(int k = 0; k < nextMoves.size(); k++){
                                if (nextMoves[k].from_x == chess_move.to_x && nextMoves[k].from_y == chess_move.to_y){
                                    can_capture = true;
                                    // cout << "Can capture\n";
                                    // cout <<"Could not choose: " << promotionPiecesBlack[j] << endl;
                                    // cout << "from: " << nextMoves[k].from_y << ',' << nextMoves[k].from_x << endl;
                                    // cout << "to: " << nextMoves[k].to_y << ',' << nextMoves[k].to_x << endl;
                                    // cout << "Length before pop: " << m_black_pieces.size() << endl;
                                    m_black_pieces.back() = nullptr;
                                    m_black_pieces.pop_back();
                                    // cout << "Length after pop: " << m_black_pieces.size() << endl;
                                    // cout << "\n"<<endl;

                                    removePiece(chess_move.to_x,chess_move.to_y);
                                    break;
                                }
                            }
                            
                            
                        if (!can_capture){
                            // cout << "Can not capture, Success\n";
                            // cout << "Chose: " << promotionPiecesBlack[j] << endl;
                            return;
                        }
            
                        }


                    if (can_capture){
                        // cout << "No black piece that does not capture\nDo random promotion" << endl;
                        int random = rand() % 4;
                        createPiece(promotionPiecesBlack[random],chess_move.to_x,chess_move.to_y);
                        return;
                        }
                    }   

                }
            }

        }

}




void ChessBoard::removePiece(int x, int y){
    // remove piece from board
    m_state(y,x) = nullptr;
}




void ChessBoard::boardSetup(){
    if (m_state.cols() == 0 && m_state.rows() == 0){
       m_state = Matrix<shared_ptr<ChessPiece>>(8);
    }
}

shared_ptr<ChessPiece> & ChessBoard::getcell(int x, int y){
    return m_state(y,x);

}

int ChessBoard::getOppElement(ChessMove chess_move){

    if (chess_move.piece->m_is_white){

        for (int i = 0; i < m_black_pieces.size(); i++){
            if (m_black_pieces[i] == nullptr){
                continue;
            }
            else{
            vector<int> pos = m_black_pieces[i]->piecePos();
            if (vector<int>{chess_move.to_x,chess_move.to_y} == pos){

                return i;
            }}
        }

    }
    else{ //Black

        for (int i = 0; i < m_white_pieces.size(); i++){
            if (m_white_pieces[i] == nullptr){
                continue;
            }
            else{
            vector<int> pos = m_white_pieces[i]->piecePos();
            
            if (vector<int>{chess_move.to_x,chess_move.to_y} == pos){
                return i;
            }}
        }

    }
        
    return -1;

}





    void ChessBoard::deleteBoard(){
        auto board = m_state;

        for (int k = 0 ; k < 8; k++){
                for (int l = 0; l < 8; l++){
                    if (board(k,l) != nullptr){
                        board(k,l) = nullptr;
                    }
                    
                }}


        for (int i = 0; i < m_white_pieces.size(); i++){
            if (m_white_pieces[i] != nullptr){
                m_white_pieces[i] = nullptr;
            }
        }

        for (int i = 0; i < m_black_pieces.size(); i++){
            if (m_black_pieces[i] != nullptr){
                m_black_pieces[i] = nullptr;
            }
        }

    }

void ChessBoard::setcell(int x, int y, shared_ptr<ChessPiece> piece){

    if (piece.get()->m_is_white){

        for (int i = 0; i < m_white_pieces.size(); i++){
            if (m_white_pieces[i] == nullptr){
                m_white_pieces[i] = piece.get();
                break;}}
    }
    else{

        for (int i = 0; i < m_black_pieces.size(); i++){
            if (m_black_pieces[i] == nullptr){
                m_black_pieces[i] = piece.get();
                break;}}
    }

    m_state(y,x) = piece;
}



ChessBoard & ChessBoard::copyBoard(ChessMove chess_move,ChessBoard & cbOld){
    

    for (int i =0 ; i < 8; i++){
        for (int j = 0; j < 8; j++){
            m_state(i,j) = cbOld.m_state(i,j);
        }
    }

    for (int i = 0; i < m_black_pieces.size(); i++){
        if (m_black_pieces[i] != cbOld.m_black_pieces[i]){
            vector<int> posOld = cbOld.m_black_pieces[i]->piecePos();
            m_black_pieces[i] = cbOld.m_black_pieces[i];
        }
        else{
            if (!chess_move.piece->m_is_white && m_black_pieces[i] != nullptr && cbOld.m_black_pieces[i] != nullptr){
                vector<int> posOld = cbOld.m_black_pieces[i]->piecePos();
                if (posOld[0] == chess_move.to_x && posOld[1] == chess_move.to_y){
                    m_black_pieces[i]->updatePos(chess_move.from_x,chess_move.from_y);
                    vector<int> posNew = m_black_pieces[i]->piecePos();
                    
                }
            
            
            }
        }
        }

    for (int i = 0; i < m_white_pieces.size(); i++){
        if (m_white_pieces[i] != cbOld.m_white_pieces[i]){
            vector<int> posOld = cbOld.m_white_pieces[i]->piecePos();
            m_white_pieces[i] = cbOld.m_white_pieces[i];
        }
        else{
            if (chess_move.piece->m_is_white && m_white_pieces[i] != nullptr && cbOld.m_white_pieces[i] != nullptr){
                vector<int> posOld = cbOld.m_white_pieces[i]->piecePos();
                if (posOld[0] == chess_move.to_x && posOld[1] == chess_move.to_y){

                    m_white_pieces[i]->updatePos(chess_move.from_x,chess_move.from_y);
                    vector<int> posNew = m_white_pieces[i]->piecePos();
                }
            
            
            }
        }
    }

    return *this;
}
