#include "MonteCarloTreeSearch.h"
#include "ConnectFour.h"


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
	if(winner == ConnectFour::Player::PLAYER_X) {
		std::cout << "X wins" << std::endl;
	} else {
		std::cout << "O wins" << std::endl;
	}
	std::cout << "Game Over" << std::endl;
}

int main() {

	playConnectFour();

	return 0;
}
