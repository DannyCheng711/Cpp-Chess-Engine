# The final executable
chess: ChessMain.o ChessPiece.o ChessGame.o
	g++ -Wall -g -std=c++17 ChessMain.o ChessPiece.o ChessGame.o -o Chess

# Compile ChessMain.cpp to ChessMain.o
ChessMain.o: ChessMain.cpp
	g++ -Wall -g -std=c++17 -c ChessMain.cpp

# Compile ChessPiece.cpp to ChessPiece.o
ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -Wall -g -std=c++17 -c ChessPiece.cpp

# Compile ChessGame.cpp to ChessGame.o
ChessGame.o: ChessGame.cpp ChessGame.h ChessPiece.h
	g++ -Wall -g -std=c++17 -c ChessGame.cpp
