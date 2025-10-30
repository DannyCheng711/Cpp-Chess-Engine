#ifndef CHESSGAME_H
#define CHESSGAME_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

/* forward declaration of ChessPiece class */
class ChessPiece;

/* ChessGame class represents the entire chess game */
class ChessGame {

  private:
    // 8x8 board that holds pointers to ChessPiece objects
    ChessPiece* board[8][8];
    // Flag indicating whether it's white's turn to move
    bool whiteToMove;
    // String representing the castling rights in FEN notation
    string castlingRights;
  
  public:
    // Constructor initializes a new chess game
    ChessGame();
    // Destructor cleans up dynamically allocated memory
    ~ChessGame();

    /* Loads the chess game state from a FEN string */
    void loadState(const char* fen);
    /* Submits a move from one position to another */
    void submitMove(const char* pos_from, const char* pos_to);
    /* Prints the current state of the chessboard */
    void printBoard() const;
    /* Checks if the king of the given color is in a safe position */
    bool isKingSafe(const bool kingIsWhite);
    /* Finds and returns the position of the king for the specified color */
    pair<int, int> findKingPos(char kingType);
    /* Checks if the given player's opponent is in checkmate */
    bool isCheckMate(const bool opponentIsWhite);
    /* Checks if the given player's opponent is in stalemate */
    bool isStaleMate(const bool opponentIsWhite);
    /* Performs a temporary move on the board for the given piece */
    void performTemporaryMove(ChessPiece*& piece, int startRow, int startCol, int endRow, int endCol, ChessPiece*& capturedPiece);
    /* Undoes a temporary move and restores the previous state */
    void undoTemporaryMove(ChessPiece*& piece, int startRow, int startCol, int endRow, int endCol, ChessPiece*& capturedPiece);

     /* Creates a new ChessPiece of the specified type at the given position */
    ChessPiece* createChessPiece(char type, int row, int col);
};

#endif
