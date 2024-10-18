all:
	g++ finalCHess.cpp ChessBoard.cpp King.cpp Rook.cpp Bishop.cpp Queen.cpp Knight.cpp Pawn.cpp ChessPiece.cpp RandomThinker.cpp OnestepAhead.cpp	
test:
	./a.out < ai.in

test_valgrind:
	valgrind ./a.out < ai.in
	
clean:
	rm a.out