#include "MonteCarloTreeSearch.hpp"
#include <fstream>


int main(int argc, char *argv[]) {
	srand((unsigned)time(0));

	ConnectFour game {6,7};
	ConnectFourState start {game.getGameState()};
	Node<ConnectFourState> root {nullptr, start};
	ConnectFourState winner {Player::PLAYER_X};
	ConnectFourState loser {Player::PLAYER_O};

	MonteCarloTreeSearch<ConnectFourState> mcts {&root, winner, loser};

	// Play Connect Four against AI
	auto playConnectFourAI = [&](){
		bool playerTurn = false;
		while(!game.checkWin()) {
			std::cout << game.displayBoard() << std::endl;
			if(!playerTurn) {
				std::cout << "Thinking" << std::endl;
				mcts.runSearch();
				game.setGameState(mcts.playBestState());
			} else {
				int userInput;
				std::cout << "play Move: " << std::endl;
				std::cin >> userInput;
				std::cout << "\n";
				game.playMove(userInput);
				//Node<ConnectFourState> s {nullptr, game.getGameState()};
				mcts.getCurrentGameState(game.getGameState());
			}
			playerTurn = !playerTurn;
		}
		std::cout << game.displayBoard() << std::endl;
		auto winner = game.getWinner();
		if(winner == Player::PLAYER_X) {
			std::cout << "X wins" << std::endl;
		} else {
			std::cout << "O wins" << std::endl;
		}
		std::cout << "Game Over" << std::endl;
	};

	playConnectFourAI();

	return 0;
}


