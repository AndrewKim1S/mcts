#pragma once

#include "GameState.h"
#include <string>


class ConnectFourState : GameState {

};

class ConnectFour {

	public:
		enum class Player {
			PLAYER_X,
			PLAYER_O,
			NONE
		};

		ConnectFour(int rows = 6, int cols = 7);
		~ConnectFour();
		std::string displayBoard();

		bool playMove(int col);
		bool checkWin();
		ConnectFourState getGameState();
		Player getWinner() {
			return _winner;
		}


	private:
		int _rows;
		int _cols;

		std::vector<std::vector<Player>> _board;
		Player _currentPlayer;
		Player _winner;

		std::string _btmHeader;
};

