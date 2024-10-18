//
// DD1388 - Lab 4: Losing Chess
//

#include "ChessBoard.h"
#include <string>
using namespace std;

// Implement additional functions or classes of your choice

int main() {
    // Implement the AIs hereint main() {
    ChessBoard board;
    vector<ChessMove> moves;
    vector<ChessMove> nonMoves;
    try {
        // Test boards from stdin
        int board_id = 1;
        while (!cin.eof()) {
            // print cin
            string line;
            // cin >> line;
            cin >> board;
            // cout << line << endl;
            ++board_id;
        }
        moves = board.capturingMoves(0);
        // nonMoves = board.nonCapturingMoves(0);
        cout <<" There were " << moves.size() <<" capturing moves" << endl;
        cout << "All tests were successful" << endl;

        // cout << board ;
    } catch (std::runtime_error & error) {
        cerr << error.what() << endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
