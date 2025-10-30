#include "ChessPiece.h"

// ChessPiece constructor: initializes piece type, row, and column
ChessPiece::ChessPiece(char type, int row, int col) : type(type), row(row), col(col) {}

// ChessPiece destructor: does nothing here, but can be extended for derived classes
ChessPiece::~ChessPiece() {}

// Getter function to retrieve the type of the chess piece (e.g., 'P' for Pawn, 'R' for Rook)
char ChessPiece::getType() const {
    return type;
}

// Determines if the piece is on the white side (upper case indicates white)
bool ChessPiece::isWhiteSide() const {
    // Upper white, lower black
    return isupper(type);
}

// Sets the new position for the piece on the board
void ChessPiece::setPosition(int newRow, int newCol) {
    row = newRow; 
    col = newCol;
}

// Rook class constructor: initializes the ChessPiece base class
Rook::Rook(char type, int row, int col) : ChessPiece(type, row, col) {}

// Getter function to retrieve the name of the piece
const char* Rook::getName() const {
  return "Rook";
}

// Function to get all legal moves of the Rook
vector<pair<int, int>> Rook::getLegalMoves(ChessPiece* board[8][8]) const {
    vector<pair<int, int>> legalMoves;
    const int direction[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}}; // Down, Up, Right, Left

    // Loop through each direction and find the valid moves
    for (int i = 0; i < 4; i++) {
        int cur_row = row;
        int cur_col = col;

        while (true) {
            cur_row += direction[i][0];  // Row increment
            cur_col += direction[i][1];  // Column increment

            // Break if we go off the board
            if (cur_row < 0 || cur_row >= 8 || cur_col < 0 || cur_col >= 8) {
                break;
            }

            const ChessPiece* targetPiece = board[cur_row][cur_col];
            if (targetPiece == nullptr) {
                // If the target square is empty, the move is valid
                legalMoves.push_back(pair(cur_row, cur_col));
            } else {
                // If the target square has a piece, capture it if it's of the opposite color
                if (targetPiece->isWhiteSide() != this->isWhiteSide()) {
                    legalMoves.push_back(pair(cur_row, cur_col));
                }
                break; // Stop if a piece is encountered, whether friendly or enemy
            }
        }
    }
    return legalMoves;
}

// Pawn class constructor: initializes the ChessPiece base class
Pawn::Pawn(char type, int row, int col): ChessPiece(type, row, col){}

// Getter function to retrieve the name of the piece
const char* Pawn::getName() const {
  return "Pawn";
}

// Function to get all legal moves of the Pawn
vector<pair<int, int>> Pawn::getLegalMoves(ChessPiece* board[8][8]) const {
    
    vector<pair<int, int>> legalMoves;
    int direction;
    
    // Determine the direction of movement based on the color of the pawn
    if (this->isWhiteSide()){
      direction = 1; // white moves Up
    }else{
      direction = -1; // black moves down
    }

    // Move 1 square forward
    int cur_row = row + direction;
    if (cur_row >= 0 && cur_row < 8 && board[cur_row][col] == nullptr) {
      legalMoves.push_back(pair(cur_row, col));
    }

    // Move 2 squares forward (initial pawn move)
    // white pawn starts from row 2 and black pawn starts from row 7
    if ((this->isWhiteSide() && row == 1) || (!this->isWhiteSide() && row == 6 )){
      int cur_row = row + 2 * direction;
      if (board[cur_row][col] == nullptr && board[row + direction][col] == nullptr) {
        legalMoves.push_back(pair(cur_row, col));
      }
    }

    // Capture diagonally (left and right)
    if (col - 1 >= 0) {
      int diag_row = row + direction;
      if (board[diag_row][col - 1] != nullptr && board[diag_row][col - 1]->isWhiteSide() != this->isWhiteSide()) {
        legalMoves.push_back(pair(diag_row, col - 1));
      }
    }

    if (col + 1 < 8) {
      int diag_row = row + direction;
      if (board[diag_row][col + 1] != nullptr && board[diag_row][col + 1]->isWhiteSide() != this->isWhiteSide()) {
        legalMoves.push_back(pair(diag_row, col + 1));
      }
    }
    
    return legalMoves;
}

// Bishop class constructor: initializes the ChessPiece base class
Bishop::Bishop(char type, int row, int col): ChessPiece(type, row, col){}

// Getter function to retrieve the name of the piece
const char* Bishop::getName() const {
  return "Bishop";
}

// Function to get all legal moves of the Bishop
vector<pair<int, int>> Bishop::getLegalMoves(ChessPiece* board[8][8]) const {
    
    vector<pair<int, int>> legalMoves;

    // Directions for diagonal movement
    const int direction[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};                    

    // Loop through each diagonal direction and find valid moves
    for (int i = 0 ; i < 4; i++){
      int cur_row = row;
      int cur_col = col;

      while(true){
        cur_row += direction[i][0]; // row increment                                                                    
        cur_col += direction[i][1]; // column increment                                                                  
        
        // Break if we go off the board                                                                                       
        if (cur_row < 0 || cur_row >= 8 || cur_col < 0 || cur_col >=8 ){
          break;
        }

        const ChessPiece* targetPiece  = board[cur_row][cur_col];
        if (targetPiece == nullptr) {
          // If the target square is empty, the move is valid
          legalMoves.push_back(pair(cur_row, cur_col));
        }else{
          // If the target square has a piece, capture it if it's of the opposite color                                                                                     
          if (targetPiece->isWhiteSide() != this->isWhiteSide()){
            legalMoves.push_back(pair(cur_row, cur_col));
          }
          break; // Stop if a piece is encountered
        }
      }
    }
    return legalMoves;
}
                                                                                                                                          
// Queen class constructor: initializes the ChessPiece base class
Queen::Queen(char type, int row, int col): ChessPiece(type, row, col){} 

// Getter function to retrieve the name of the piece
const char* Queen::getName() const {
  return "Queen";
}

// Function to get all legal moves of the Queen
vector<pair<int, int>> Queen::getLegalMoves(ChessPiece* board[8][8]) const {
    vector<pair<int, int>> legalMoves;
    const int direction[8][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    // Loop through each direction and find valid moves
    for (int i = 0 ; i < 8; i++){
        int cur_row = row;
        int cur_col = col;
        
        while(true){
          cur_row += direction[i][0]; // row increment
          cur_col += direction[i][1]; // column increment
            
          // Break if we go off the board
          if (cur_row < 0 || cur_row >= 8 || cur_col < 0 || cur_col >=8 ){
            break;
          }
            
          const ChessPiece* targetPiece  = board[cur_row][cur_col];
            
          if (targetPiece == nullptr) {
            // If the target square is empty, the move is valid
            legalMoves.push_back(pair(cur_row, cur_col));
          
          }else{ 
            // If the target square has a piece, capture it if it's of the opposite color
            if (targetPiece->isWhiteSide() != this->isWhiteSide()){
                legalMoves.push_back(pair(cur_row, cur_col));
            }
            break; // Stop if a piece is encountered
          }
        }
    }
    return legalMoves;
}


// Knight class constructor: initializes the ChessPiece base class
Knight::Knight(char type, int row, int col): ChessPiece(type, row, col){}

// Getter function to retrieve the name of the piece
const char* Knight::getName() const {
  return "Knight";
}

// Function to get all legal moves of the Knight
vector<pair<int, int>> Knight::getLegalMoves(ChessPiece* board[8][8]) const {
    vector<pair<int, int>> legalMoves;
    
    // Directions for L-shaped movement
    const int direction[8][2] = {
      {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, // Vertical L-shape
      {1, 2}, {1, -2}, {-1, 2}, {-1, -2} // Horizontal L-shape
    };

    // Loop through each direction and find valid moves
    for (int i = 0 ; i < 8; i++){
      int cur_row = row + direction[i][0];
      int cur_col = col + direction[i][1];

      // Break if we go off the board
      if (cur_row < 0 || cur_row >= 8 || cur_col < 0 || cur_col >=8 ){
        continue;
      }

      const ChessPiece* targetPiece  = board[cur_row][cur_col];
      if (targetPiece == nullptr) {
        // If the target square is empty, the move is valid
        legalMoves.push_back(pair(cur_row, cur_col));
      }else if (targetPiece->isWhiteSide() != this->isWhiteSide()){
        // If the target square has a piece, capture it if it's of the opposite color
        legalMoves.push_back(pair(cur_row, cur_col));
      }
    }

    return legalMoves;
  }
  

// King class constructor: initializes the ChessPiece base class
King::King(char type, int row, int col): ChessPiece(type, row, col){}

// Getter function to retrieve the name of the piece
const char* King::getName() const {
  return "King";
}

// Function to get all legal moves of the King
vector<pair<int, int>> King::getLegalMoves(ChessPiece* board[8][8]) const {
    vector<pair<int, int>> legalMoves;

    // Directions for King's movement (1 square in any direction)
    const int direction[8][2] = {
      {1, 0}, {-1, 0}, // Vertical move
      {0, 1}, {0, -1}, // Horizontal move
      {1, 1}, {1, -1}, // Diagonal move
      {-1, 1}, {-1, -1} // Diagonal move
    }; 

    // Loop through each direction and find valid moves
    for (int i = 0 ; i < 8; i++){
      int cur_row = row + direction[i][0];
      int cur_col = col + direction[i][1];

      // Break if we go off the board
      if (cur_row < 0 || cur_row >= 8 || cur_col < 0 || cur_col >=8 ){
        continue;
      }

      const ChessPiece* targetPiece  = board[cur_row][cur_col];
      if (targetPiece == nullptr) {
        // If the target square is empty, the move is valid
        legalMoves.push_back(pair(cur_row, cur_col));
      }else if (targetPiece->isWhiteSide() != this->isWhiteSide()){
      // If the target square has a piece, capture it if it's of the opposite color
	    legalMoves.push_back(pair(cur_row, cur_col));
      }
    }
    return legalMoves;
}


