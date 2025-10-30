#include <iostream>
#include <vector>
#include <string>
#include "ChessPiece.h"
#include "ChessGame.h"

using namespace std;

/* Constructor */
ChessGame::ChessGame() {    
}

  
/* Destructor */
ChessGame::~ChessGame() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];  // Deallocate any dynamically allocated chess pieces
        }
    }
}

/* Loads the board state from a FEN string */
void ChessGame::loadState(const char* fen){
    cout << "A new board state is loaded!" << endl;

    // Initialize the board by clearing existing pieces
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            board[i][j] = nullptr; // Initialize all squares to nullptr (empty)
        }
    }
    
    // Part 2: Parse the FEN string for board setup
    int row = 7, col = 0; // Start parsing from the top-left corner
    int fileSt = 0;

    while (fen[fileSt] != ' ' && fen[fileSt] != '\0') {  // Loop until space or end of string
        char ch = fen[fileSt];
        if (ch == '/'){
            // Move to the next row
            if (col != 8) {
                cerr << "Invalid FEN: Row does not have 8 squares" << endl;
                exit(1);
            }
            row--;
            col = 0; // Reset column to the first square
        } else if (isdigit(ch)){
            // Skip empty squares
            int emptySquares = ch - '0';
            if (emptySquares < 1 || emptySquares > 8 || col + emptySquares > 8){
                cerr << "Invalid FEN: Invalid empty square count" << endl;
                exit(1);
            }
            col += emptySquares; // Move to next non-digit column
        
        } else if (isalpha(ch)){
            // Validate and create pieces based on the character
            if (ch != 'p' && ch != 'n' && ch != 'b' && ch != 'r' && ch != 'q' && ch != 'k' &&
                ch != 'P' && ch != 'N' && ch != 'B' && ch != 'R' && ch != 'Q' && ch != 'K' ){
                cerr << "Invalid FEN: Invalid chess piece. " << endl;
                exit(1);
            }
            // Place a piece
            board[row][col] = createChessPiece(ch, row, col);
            col++; // Move to next column 
        
        } else {
            cerr << "Invalid FEN: Unrecognized character" << ch << endl;
            exit(1);
        }

        fileSt++;  // Move to the next character
    }

    if (row != 0 || col != 8){
        cerr << "Error: Incomplete board setup" << endl;
        exit(1);
    }

    // Part 2: Determine the active color
    fileSt++;  // Skip the space after the board part
    while (fen[fileSt] != ' ' && fen[fileSt] != '\0') {  // Loop until space or end of string
        if (fen[fileSt] == 'w') {           
            whiteToMove = true;
        } else if (fen[fileSt] == 'b') {
            whiteToMove = false;
        } else {
            cerr << "Invalid FEN: Invalid active color" << endl;
            exit(1);
        }
        fileSt++;  // Increment to move to the next character
    }


    // Part 3: Castling Status 
    fileSt++; // Skip the space after active color
    while (fen[fileSt] != ' ' && fen[fileSt] != '\0') {  // Loop until space or end of string
        fileSt++; 
    } 
}  


/* Finds the position of the king on the board */
pair<int, int> ChessGame::findKingPos(char kingType){
    // Iterate through the board to find the king with the given type
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){
            ChessPiece* piece = board[row][col];
            if (piece && piece->getType() == kingType) {
                // King found, return its position as (row, col)
                return make_pair(row, col);
            }
        }
    }
    // If the king cannot be found, return an invalid position (-1, -1)
    return make_pair(-1, -1);
}

/* Checks if the king of the specified color is safe from attacks */
bool ChessGame::isKingSafe(const bool kingIsWhite) {
    // Identify the king's type based on the color (white or black)
    char kingType = kingIsWhite ? 'K' : 'k';

    // Find the king's current position on the board
    pair<int, int> kingPos = findKingPos(kingType);
    int kingRow = kingPos.first;
    int kingCol = kingPos.second;

    // Ensure the king exists on the board
    if (kingRow == -1 || kingCol == -1) {
        cout << endl;
        cerr << "Error: King not found on the board!" << endl;
        exit(1);
    }

    // Iterate through all pieces on the board to check for threats
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++){

            ChessPiece* piece = board[row][col];
            // Skip empty squares and pieces of the same color as the king
            if (piece && piece->isWhiteSide() != kingIsWhite) {
                // Get all legal moves for the opponent's piece
                vector<pair<int,int>> legalMoves = piece->getLegalMoves(board);
                // Check if any move targets the king's position
                for (size_t moveIndex = 0; moveIndex < legalMoves.size(); moveIndex++) {
                    if (legalMoves[moveIndex].first == kingRow && 
                        legalMoves[moveIndex].second == kingCol) {
                        return false; // King is in danger
                    }
                }
            }
        }
    }

    return true; // King is safe from all threats
}

/* Helper to perform a temporary move on the chessboard */
void ChessGame::performTemporaryMove(
    ChessPiece*& piece, int startRow, int startCol, int endRow, int endCol, ChessPiece*& capturedPiece) {
    // Move the piece to the target square
    board[endRow][endCol] = piece;
    // Clear the piece from its original square
    board[startRow][startCol] = nullptr;
    // Update the piece's internal position to reflect the new location
    piece->setPosition(endRow, endCol);
}

/* Helper to undo a temporary move on the chessboard */
void ChessGame::undoTemporaryMove(
    ChessPiece*& piece, int startRow, int startCol, int endRow, int endCol, ChessPiece*& capturedPiece) {
    // Move the piece back to its original square
    board[startRow][startCol] = piece;
    // Restore the captured piece (if any) to its original position
    board[endRow][endCol] = capturedPiece;
    // Update the piece's internal position to its original location
    piece->setPosition(startRow, startCol);
}


/* Check if the opponent's king is in checkmate */
bool ChessGame::isCheckMate(const bool opponentIsWhite) {
    
    // 1. Check if the opponent's king has any legal moves to escape from check 
    char kingType = opponentIsWhite ? 'K' : 'k';
    pair<int, int> kingPos = findKingPos(kingType);
    int kingRow = kingPos.first;
    int kingCol = kingPos.second;

    ChessPiece* kingPiece = board[kingRow][kingCol];

    // Get all legal moves for the opponent's king
    vector<pair<int,int>> kingLegalMoves = kingPiece->getLegalMoves(board);
    // Check all legal moves of the king
    for (size_t i = 0; i < kingLegalMoves.size(); i++) {
        int endRow = kingLegalMoves[i].first;
        int endCol = kingLegalMoves[i].second; 

        ChessPiece* capturedPiece = board[endRow][endCol]; // Save the piece being captured (if any) 
        // Perform temporary move
        performTemporaryMove(kingPiece, kingRow, kingCol, endRow, endCol, capturedPiece);

        // Check if the move allows the king to escape check
        if (isKingSafe(opponentIsWhite)) {
            // Undo the move if the king is safe
            undoTemporaryMove(kingPiece, kingRow, kingCol, endRow, endCol, capturedPiece);
            return false; // The king can escape, so it's not checkmate
        } 

        // Undo the move
        undoTemporaryMove(kingPiece, kingRow, kingCol, endRow, endCol, capturedPiece);

    }

    // 2. Check if any of the opponent's pieces can block or capture the checking piece
    for (int startRow = 0; startRow < 8; startRow++) {
        for (int startCol = 0; startCol < 8; startCol++){
            if (!(startRow == kingRow && startCol == kingCol)){
                
                ChessPiece* otherPiece = board[startRow][startCol];

                // Check if the piece belongs to the opponent
                if (otherPiece && otherPiece->isWhiteSide() == opponentIsWhite){
                    // Get all legal moves for this piece
                    vector<pair<int,int>> otherPieceLegalMoves = otherPiece->getLegalMoves(board);
                    
                    // Check all legal moves of the opponent's piece
                    for (size_t i = 0; i < otherPieceLegalMoves.size(); i++) {
                        int endRow = otherPieceLegalMoves[i].first;
                        int endCol = otherPieceLegalMoves[i].second; 

                        ChessPiece* capturedPiece = board[endRow][endCol]; // Save the piece being captured (if any)
                        // Perform temporary move
                        performTemporaryMove(otherPiece, startRow, startCol, endRow, endCol, capturedPiece);
                        // Check if the move allows the king to escape check
                        if (isKingSafe(opponentIsWhite)) {
                            // Undo the move if the king is safe
                            undoTemporaryMove(otherPiece, startRow, startCol, endRow, endCol, capturedPiece);
                            return false; // The opponent can escape the check, so it's not checkmate
                        }
                        // Undo the move
                        undoTemporaryMove(otherPiece, startRow, startCol, endRow, endCol, capturedPiece);

                    }
                }
            }
        }
    }
    
    return true; // If no escape moves are found, it's checkmate
}

/* Check if the opponent is in a stalemate situation */
bool ChessGame::isStaleMate(const bool opponentIsWhite) {
    // 1. Check if the opponent has any feasible moves that don't put their king in danger
    for (int startRow = 0; startRow < 8; startRow++) {
        for (int startCol = 0; startCol < 8; startCol++){
            // Get the piece at the current position
            ChessPiece* opponentPiece = board[startRow][startCol];
            // Proceed only if it's the opponent's piece
            if (opponentPiece && opponentPiece->isWhiteSide() == opponentIsWhite){
                // Get all legal moves for the opponent's piece
                vector<pair<int,int>> legalMoves = opponentPiece->getLegalMoves(board);
                // 2. Check if any legal move would leave the opponent's king in danger (in check)
                for (size_t moveIndex = 0; moveIndex < legalMoves.size(); moveIndex++) {
                    int endRow = legalMoves[moveIndex].first;
                    int endCol = legalMoves[moveIndex].second;
                    
                    // Perform temporary move
                    ChessPiece* capturedPiece = board[endRow][endCol]; // Save the piece being captured (if any) 
                    performTemporaryMove(opponentPiece, startRow, startCol, endRow, endCol, capturedPiece);
                    // Check if the move leaves the king in check
                    if (!isKingSafe(opponentPiece->isWhiteSide())) {
                        // Undo the move if the king would be in check
                        undoTemporaryMove(opponentPiece, startRow, startCol, endRow, endCol, capturedPiece);
                    }else{
                        // If any move leaves the king safe, it's not a stalemate
                        undoTemporaryMove(opponentPiece, startRow, startCol, endRow, endCol, capturedPiece);
                        return false; // Not a stalemate
                    }
                }
            }
        }
    }
    // 3. If no legal moves for any of the opponent's pieces result in a safe king, it's a stalemate
    return true;
}

/* Handles submitting a move in the chess game, validating positions, legal moves, 
    and ensuring the king is not in check before updating the board and switching turns. */
void ChessGame::submitMove(const char* posFrom, const char* posTo){

    // Convert input positions from chess notation to board indices
    int startRow = posFrom[1] - '1';
    int startCol = posFrom[0] - 'A';
    int endRow = posTo[1] - '1';
    int endCol = posTo[0] - 'A';

    // Validate if positions are within bounds
    if (startRow < 0 || startRow >= 8 || startCol < 0 || startCol >= 8 ||
        endRow < 0 || endRow >= 8 || endCol < 0 || endCol >= 8) {
        cout << "Move out of bounds " << endl;
        return ;
    }

    // Check if a piece exists at the source position
    ChessPiece* piece = board[startRow][startCol];
    if(piece == nullptr){
        cout << "There is no piece at position " 
        << char('A' + startCol) <<  startRow + 1 << endl;
        return ;
    } 

   // Ensure the move is made by the correct player
    if ((piece->isWhiteSide() && !whiteToMove) || (!piece->isWhiteSide() && whiteToMove)) {
        cout <<  "It is not " 
        << (piece->isWhiteSide() ? "White's " : "Black's ") 
        << "turn to move!" << endl;
        return ;
    }

    // Get the list of legal moves for the piece
    vector<pair<int,int>> legalMoves = piece->getLegalMoves(board);
    
    // Check if the destination position is a valid move
    bool isLegal = false;
    for (size_t i = 0; i < legalMoves.size(); i++) {
        if (legalMoves[i].first == endRow && legalMoves[i].second == endCol) {
            isLegal = true;
            break;
        }
    }

    if (!isLegal) {
        cout << (piece->isWhiteSide() ? "White's " : "Black's ") 
        << piece->getName() 
        << " cannot move to " << posTo << endl;

        return;
    }

    // Perform temporary move
    ChessPiece* capturedPiece = board[endRow][endCol]; // Save the piece being captured (if any) 
    performTemporaryMove(piece, startRow, startCol, endRow, endCol, capturedPiece);

    // Ensure the move does not leave the king in check
    if (!isKingSafe(piece->isWhiteSide())) {
        undoTemporaryMove(piece, startRow, startCol, endRow, endCol, capturedPiece);
        cout << "Move leaves the king in check" << endl;
        return;
    }

    // Print successful move details
    cout << (piece->isWhiteSide() ? "White's " : "Black's ") 
         << piece->getName() 
         << " moves from " << posFrom << " to " << posTo;

    // Handle captured piece, if any
    if (capturedPiece != nullptr) {
        cout << " taking " 
             << (capturedPiece->isWhiteSide() ? "White's " : "Black's ") 
             << capturedPiece->getName();
        delete capturedPiece; // Free memory if dynamically allocated
    }

    // Check for check, checkmate, or stalemate after the move
    if(!isKingSafe(!piece->isWhiteSide())){
        if (!isCheckMate(!piece->isWhiteSide())){
            cout << endl
            <<(!piece->isWhiteSide() ? "White " : "Black ") 
            << "is in check";
        }
        else{
            cout << endl
            <<(!piece->isWhiteSide() ? "White " : "Black ") 
            << "is in checkmate";
        }
    
    }else {

        if (isStaleMate(!piece->isWhiteSide())) {
            cout << endl;
            cout << "The game is in stalemate";
        }
    }

    cout << endl;

    // Switch turn to the other player
    whiteToMove = !whiteToMove; 
    
}

/* Prints the current state of the chessboard with row and column labels. */  
void ChessGame::printBoard() const {
    cout << "    a   b   c   d   e   f   g   h" << endl;  // Column labels
    cout << "  ---------------------------------" << endl;

    for (int i = 7; i >=0; i--) {
        cout << i + 1  << " ";  // Row labels

        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                // Display the piece type or symbol
                cout << "| " << board[i][j]->getType() << " ";
            } else {
                cout << "|   ";  // Empty square
	        }
        }

        cout << "|" << endl;
        cout << "  ---------------------------------" << endl;
    }
}

/* Creates and returns a new chess piece object based on the provided type, row, and column. */
ChessPiece* ChessGame::createChessPiece(char type, int row, int col){

    switch (type) {
        case 'p': return new Pawn('p', row, col);
        case 'P': return new Pawn('P', row, col);
        case 'r': return new Rook('r', row, col);  
        case 'R': return new Rook('R', row, col);
        case 'n': return new Knight('n', row, col);
        case 'N': return new Knight('N', row, col);
        case 'b': return new Bishop('b', row, col);
        case 'B': return new Bishop('B', row, col);
        case 'q': return new Queen('q', row, col);
        case 'Q': return new Queen('Q', row, col);
        case 'k': return new King('k', row, col);
        case 'K': return new King('K', row, col);

        default: return nullptr; // Invalid character  
    }
}

