//
// DD1388 - Lab 4: Losing Chess
//

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <istream>
#include <memory>
#include "ChessMove.h"
#include "Matrix.h"   // Use the "-I ../02" flag to let the compiler find Matrix.h

using namespace std;

class ChessPiece;

class ChessBoard {
    // add additional members or functions of your choice

private:
    // Alternative 1 (the matrix owns the chess pieces):
    Matrix<shared_ptr<ChessPiece>> m_state; // Matrix from lab 2
    vector<ChessPiece *> m_white_pieces;
    vector<ChessPiece *> m_black_pieces;
public:
    // std::shared_ptr<ChessPiece> savedPiece;
    // std::shared_ptr<ChessPiece> wPiece; 

    // Alternative 2 (the vectors own the chess pieces):
    // Matrix<ChessPiece *> m_state; // Matrix from lab 2
    // vector<shared_ptr<ChessPiece>> m_white_pieces;
    // vector<shared_ptr<ChessPiece>> m_black_pieces;


    void movePiece(ChessMove chess_move);

    vector<ChessMove> capturingMoves(bool is_white);
    vector<ChessMove> nonCapturingMoves(bool is_white);
    void pawnpromotion(ChessMove chess_move);
    void smartPawnPromotion(ChessMove chess_move);
    void removePiece(int x, int y);
    bool gameover();
    void printPieces();
    int getOppElement(ChessMove chess_move);
    void deleteBoard();
    
    Matrix<shared_ptr<ChessPiece>> & getBoard();
    void boardSetup();
    void createPiece(char piece, int x, int y);
    shared_ptr<ChessPiece> & getcell(int x, int y);
    void setcell(int x, int y, shared_ptr<ChessPiece> piece);
    ChessBoard & copyBoard(ChessMove chess_move,ChessBoard & cbOld);

    

};

ChessBoard & operator>>(istream & is, ChessBoard & cb);
ChessBoard & operator<<(ostream & os, ChessBoard & cb);

#endif //CHESSBOARD_H