# Chess Engine

A compact chess engine project implemented in C++ for practicing move generation, FEN parsing, move validation, and simple check/checkmate/stalemate detection.

---

### Exercise Summary
- Implements a chess board representation, FEN loader, move validation per piece, and basic game-state checks (check, checkmate, stalemate).


--- 
### Key components
- **Board & game logic:** See implementation in [`ChessGame.cpp`](ChessGame.cpp).
  - FEN loader: [`ChessGame::loadState`](ChessGame.cpp)
  - Move submit / validation: [`ChessGame::submitMove`](ChessGame.cpp)
  - King safety and game state checks: [`ChessGame::isKingSafe`](ChessGame.cpp), [`ChessGame::isCheckMate`](ChessGame.cpp), [`ChessGame::isStaleMate`](ChessGame.cpp)
  - Helpers: [`ChessGame::performTemporaryMove`](ChessGame.cpp), [`ChessGame::undoTemporaryMove`](ChessGame.cpp)
- **Piece hierarchy:** See implementations in [`ChessPiece.cpp`](ChessPiece.cpp)
  - Move generation interface: [`ChessPiece::getLegalMoves`](ChessPiece.h)
  - Helpers: [`ChessPiece::isWhiteSide`](ChessPiece.cpp), [`ChessPiece::setPosition`](ChessPiece.cpp)

--- 

### Usage

```sh
make          # Build the program
make clean    # Remove object files and executable
./Chess    # Run the program
```

---

### Sample Output

Below is an example of the program execution showing chess movement, board update and game-state checks.

```text
=========================
Alekhine vs. Vasic (1931)
=========================

A new board state is loaded!

White's Pawn moves from E2 to E4
Black's Pawn moves from E7 to E6

White's Pawn moves from D2 to D4
Black's Pawn moves from D7 to D5

White's Knight moves from B1 to C3
Black's Bishop moves from F8 to B4

White's Bishop moves from F1 to D3
Black's Bishop moves from B4 to C3 taking White's Knight
White is in check

White's Pawn moves from B2 to C3 taking Black's Bishop
Black's Pawn moves from H7 to H6

White's Bishop moves from C1 to A3
Black's Knight moves from B8 to D7

White's Queen moves from D1 to E2
Black's Pawn moves from D5 to E4 taking White's Pawn

White's Bishop moves from D3 to E4 taking Black's Pawn
Black's Knight moves from G8 to F6

White's Bishop moves from E4 to D3
Black's Pawn moves from B7 to B6

White's Queen moves from E2 to E6 taking Black's Pawn
Black is in check
Black's Pawn moves from F7 to E6 taking White's Queen

White's Bishop moves from D3 to G6
Black is in checkmate
```


---

### Acknowledgement

- **Program:** MSc Computing, Imperial College London  
- **Module:** Principles and Practice of Programming
