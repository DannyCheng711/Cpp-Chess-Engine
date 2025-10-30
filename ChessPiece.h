#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>
#include <cctype>

using namespace std;

// Base class for all chess pieces
class ChessPiece {
private:
  char type; // Type of the piece (e.g., 'K' for King, 'Q' for Queen)
  
public:
  // Pure virtual function to get the name of the piece (must be implemented in derived classes)
  virtual const char* getName() const = 0;
  // Function to get the type of the piece
  char getType() const; 
  // Function to check if the piece is on the white side
  bool isWhiteSide() const;
  // Position of the piece on the board (row and column)
  int row, col;
  
  // Constructor to initialize the piece with a type and position
  ChessPiece(char type, int row, int col);

  // Virtual destructor to ensure proper cleanup of derived classes
  virtual ~ChessPiece(); 
  
  // Function to set the position of the piece on the board
  void setPosition(int newRow, int newCol);

  // Pure virtual function to get all legal moves of the piece (must be implemented in derived classes)
  virtual vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const = 0; // Pure virtual function
};

// Derived class for Rook piece
class Rook : public ChessPiece {
public:
  Rook(char type, int row, int col); // Constructor

  const char* getName() const override; // Override to return the name of the piece

  // Function to get all legal moves for the Rook
  vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const override;
};

// Derived class for Pawn piece
class Pawn: public ChessPiece {
 public:
  Pawn(char type, int row, int col); // Constructor

  const char* getName() const override; // Override to return the name of the piece

  // Function to get all legal moves for the Pawn
  vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const override;
};

// Derived class for Bishop piece
class Bishop: public ChessPiece {
public:
  Bishop(char type, int row, int col); // Constructor

  const char* getName() const override; // Override to return the name of the piece

  // Function to get all legal moves for the Bishop
  vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const override;
};

// Derived class for Queen piece
class Queen: public ChessPiece {
public:
  Queen(char type, int row, int col); // Constructor

  const char* getName() const override; // Override to return the name of the piece

  // Function to get all legal moves for the Queen
  vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const override;
};

// Derived class for Knight piece
class Knight: public ChessPiece {
public:
  Knight(char type, int row, int col); // Constructor

  const char* getName() const override; // Override to return the name of the piece

  // Function to get all legal moves for the Knight
  vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const override;
};

// Derived class for King piece
class King: public ChessPiece {
public:
  King(char type, int row, int col);  // Constructor

  const char* getName() const override; // Override to return the name of the piece

  // Function to get all legal moves for the King
  vector<pair<int, int>> getLegalMoves(ChessPiece* board[8][8]) const override;
};

#endif // CHESSPIECE_H