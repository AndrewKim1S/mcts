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

	// playConnectFour();

	ConnectFour game {6,7};

	ConnectFourState start {game.getGameState()};
	auto nextStates = start.getAllPossibleStates();
	for(auto &x : nextStates) {
		std::cout << x << std::endl;
	}
	
	Node<ConnectFourState> root {nullptr, start};

	MonteCarloTreeSearch<ConnectFourState> mcts {&root};
	mcts.runSearch();


	return 0;
}
