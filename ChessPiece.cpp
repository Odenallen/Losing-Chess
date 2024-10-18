//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessPiece.h"
#include "ChessBoard.h"

int ChessPiece::validMove(int to_x, int to_y) {
    // Implementation goes here

    return 0;
}

string ChessPiece::utfRepresentation() {
    // Implementation goes here
    return "yayayya I am lord!";
}

char ChessPiece::latin1Representation() {
    // Implementation goes here
    return 'c';
}

ChessPiece::ChessPiece(int x, int y, bool is_white, ChessBoard *board)
/*:  Initialize members here */ {
    // or here ...
    m_x = x;
    m_y = y;
    m_is_white = is_white;
    m_board = board;
}

ChessPiece::ChessPiece(){
    m_x = 0;
    m_y = 0;
    m_is_white = true;
    m_board = nullptr;

}

bool ChessPiece::capturingMove(int to_x, int to_y) {
    // Implementation goes here
    if (validMove(to_x,to_y) == 2){
        return true;
    }
    return false;
}

bool ChessPiece::nonCapturingMove(int to_x, int to_y) {
    // Implementation goes here
    if (validMove(to_x,to_y) == 1){
        return true;
    }
    return false;
}

vector<ChessMove> ChessPiece::capturingMoves() {
    // Implementation goes here
    vector<ChessMove> moves;
    return moves;

}

vector<ChessMove> ChessPiece::nonCapturingMoves() {
    // Implementation goes here
    vector<ChessMove> moves;
    return moves;

}
vector<int> ChessPiece::piecePos(){
    vector<int> position{m_x,m_y};
    return position;
}
void ChessPiece::updatePos(int x, int y){
    m_x = x;
    m_y = y;
}