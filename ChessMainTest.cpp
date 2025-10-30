#include <iostream>
#include "ChessGame.h"

using std::cout;


int main() {


	ChessGame cg;
	
    cout << "========================================\n";
	cout << "Pawn Movement (No Obstacle)\n";
	cout << "========================================\n";

    cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cg.submitMove("E2", "E4");
    cg.submitMove("E7", "E5"); 
	cout << '\n';
	
    cout << "========================================\n";
	cout << "Bishop Diagonal Movement (Valid Move)\n";
	cout << "========================================\n";

    cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cg.submitMove("E2", "E4");
    cg.submitMove("E7", "E5");
	cg.submitMove("F1", "C4");
	cout << '\n';

	
    cout << "========================================\n";
	cout << "Bishop Diagonal Movement (with Obstacle)\n";
	cout << "========================================\n";

    cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cg.submitMove("F1", "C4");
	cout << '\n';

	
    cout << "========================================\n";
	cout << "King Movement (Valid Move)\n";
	cout << "========================================\n";

    cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cg.submitMove("E2", "E4");
    cg.submitMove("E7", "E5");
	cg.submitMove("E1", "E2");
	cout << '\n';
	


	cout << "========================================\n";
	cout << "Queen Movement (Valid Move)\n";
	cout << "========================================\n";

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq ");
	cg.submitMove("E2", "E4");
	cg.submitMove("D7", "D5");
	cg.submitMove("D1", "F3");
	
	cout << "========================================\n";
	cout << "Queen Movement (Invalid Move)\n";
	cout << "========================================\n";

	// Load a custom FEN to test invalid queen movement
	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");

	cg.printBoard();
	cg.submitMove("E2", "E4");
	cg.submitMove("D7", "D5");
	cg.submitMove("D1", "D3"); 
	cg.printBoard();
	cout << '\n';
	
	
	// rook 
	cout << "========================================\n";
	cout << "Rook Movement (Invalid Move)\n";
	cout << "========================================\n";

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR b KQkq");
	cg.submitMove("A8", "B4"); 
	cg.printBoard();
	cout << '\n';

	cout << "========================================\n";
	cout << "Rook Movement (Capture Opponent)\n";
	cout << "========================================\n";

	cg.loadState("rnbqkbnr/pp1pp1pp/4p2p/6P1/8/2P5/PPP1PPP1/RNBQKBNR w KQkq");  // Rook on D1, Queen on D4
	cg.printBoard();
	cg.submitMove("H3", "G4"); 
	cg.submitMove("H1", "H6");  // Rook captures Pawn
	cg.printBoard();
	cout << '\n';


	cout << "========================================\n";
	cout << "Check Mate Test (Legals Mate)\n";
	cout << "========================================\n";

	cg.loadState("r2qkbnr/ppp1pppp/3p4/4N3/2B1P3/2N5/PPPP1PPP/R1BbK2R w KQkq");
	cg.printBoard();
	cg.submitMove("C4", "F7");

	cout << "========================================\n";
	cout << "Check Mate Test (Anastasias Mate)\n";
	cout << "========================================\n";

	cg.loadState("5r1k/pbrnNpp1/1pp5/2P1p2q/3P4/1P5R/P4PPP/5RK1 w KQkq");
	cg.printBoard();
	cg.submitMove("H3", "H5");

	cout << "========================================\n";
	cout << "Check Mate Test (Grecos Mate)\n";
	cout << "========================================\n";

	cg.loadState("k3r3/pp1r2p1/7p/2p2p2/2Np4/3R2BP/PPP3P1/6K1 w KQkq");
	cg.printBoard();
	cg.submitMove("C4", "B6"); // in check
	cg.submitMove("A7", "B6");
	cg.submitMove("D3", "A3"); // in check mate

	cout << "========================================\n";
	cout << "Check Mate Test (Hooks Mate)\n";
	cout << "========================================\n";

	cg.loadState("2b1Q3/1kp5/p1Nb4/3P4/1P5p/p6P/K3R1P1/5q2 w KQkq");
	cg.printBoard();
	cg.submitMove("E8", "C8"); // in check
	cg.submitMove("B7", "C8"); 
	cg.submitMove("E2", "E8"); // in check 
	cg.submitMove("C8", "D7");
	cg.submitMove("E8", "D8"); // check mate

	cout << "========================================\n";
    cout << "Stale Mate Test (Stale Mate)\n";
    cout << "========================================\n";

 
    cg.loadState("8/8/8/8/6p1/8/5k2/7K b KQkq");
    cg.printBoard();
    cg.submitMove("G4", "G3");
	cg.printBoard();
 
	
	return 0;
}
