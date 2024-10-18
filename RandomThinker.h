#include "ChessBoard.h"
#ifndef RANDOMTHINKER_H
#define RANDOMTHINKER_H

using namespace std;

class RandomThinker {
    // add additional members or functions of your choice
    public:
        bool is_white;
        RandomThinker();    
        void playerMove(ChessBoard & cb);

};
#endif