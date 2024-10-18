#include "ChessBoard.h"
#include <iostream>
#include <sstream>
#include <string>
#include "OnestepAhead.h"
#include "RandomThinker.h"


using namespace std;   




int main() {
    cout << "Welcome to the final chess game, with two AIs!! \n"<<endl;
    string line;
    stringstream board_ss;

    ChessBoard board;


    for (size_t i = 0; i < 8; ++i) {
            if (!getline(cin, line)) {
                // throw runtime_error("Could not read board #" + to_string(board_id) + ".");
                throw runtime_error("faulty input");

            }
            board_ss << line.substr(0, 8);
            }
            board_ss >> board;
            cout << board;
            cout << "\n--------------------------------\n";

            // OneStepAhead thinker1;
            // cout <<"Thinker1 smart and white"<<endl;
            RandomThinker thinker1;

            // RandomThinker thinker2;
            // cout << "Thinker2 dumb and black"<<endl;
            OneStepAhead thinker2;
            // thinker1.is_white = false;
            thinker1.is_white = true;
            // thinker2.is_white = true;
            thinker2.is_white = false;
            // cout << "Thinker1 is white: " << thinker1.is_white << endl;
            // cout << "Thinker2 is white: " << thinker2.is_white << endl;
            srand(time(0));
             int iter = 0;
            // while (true)
            while (board.gameover() == false && iter < 1000)
            // while (board.gameover() == false && iter < 5)
            {
                // cout << "we in the loop, iter : " << iter << endl;
                thinker1.playerMove(board);
                cout << board;
                if (board.gameover() == true){
                    break;
            
                }
                cout << "\n--------------------------------\n";
                thinker2.playerMove(board);
                cout << board;
                cout << "\n--------------------------------\n";


                iter++;
                // break; 
            }
            // cout << board;
            cout << "Game over! \n";
            
















}