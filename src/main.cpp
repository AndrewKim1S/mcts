#include "MonteCarloTreeSearch.hpp"
#include <fstream>


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

	ConnectFour game {6,7};

	ConnectFourState start {game.getGameState()};
	auto nextStates = start.getAllPossibleStates();
	
	Node<ConnectFourState> root {nullptr, start};
	ConnectFourState winner {Player::PLAYER_X};

	MonteCarloTreeSearch<ConnectFourState> mcts {&root, winner};
	mcts.runSearch();

	//std::cout << mcts << std::endl;

	/*
	std::ofstream dotFile("tree.dot");
	if(dotFile.is_open()) {
		std::string dotCode = "digraph Tree{\n";
		dotCode = mcts.getGraphviz(dotCode);
		dotCode += "}";
		dotFile << dotCode;
		dotFile.close();
	} else {
		std::cout << "unable to open file"<< std::endl;
		return 1;
	}

	system("dot -Tpng tree.dot -o tree.png");*/


	return 0;
}
