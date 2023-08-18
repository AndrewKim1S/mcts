#include "MonteCarloTreeSearch.hpp"


void playConnectFour() {
	ConnectFour game {6,7};
	while(!game.checkWin()) {
		std::cout << game.displayBoard() << std::endl;
		int userInput;
		std::cout << "play move: ";
		std::cin >> userInput;
		std::cout << "\n";
		game.playMove(userInput);
	}
	
	std::cout << game.displayBoard() << std::endl;
	auto winner = game.getWinner();
	if(winner == Player::PLAYER_X) {
		std::cout << "X wins" << std::endl;
	} else {
		std::cout << "O wins" << std::endl;
	}
	std::cout << "Game Over" << std::endl;
}


int main() {
	srand((unsigned)time(0));

	// playConnectFour();

	ConnectFour game {6,7};

	ConnectFourState start {game.getGameState()};
	auto nextStates = start.getAllPossibleStates();
	
	Node<ConnectFourState> root {nullptr, start};
	ConnectFourState winner {Player::PLAYER_X};

	// testing 
	/*for(int i = 0; i < 7; i++) {
		std::cout << root.getNewChild()->_state << std::endl;;
	}*/

	MonteCarloTreeSearch<ConnectFourState> mcts {&root, winner};
	mcts.runSearch();

	// std::cout << mcts << std::endl;
	// std::cout << "\u251C\u2500" << std::endl;


	return 0;
}
