#pragma once

#include <iostream>
#include <vector>
#include <string>


enum class Player {
			PLAYER_X,
			PLAYER_O,
			NONE
};


class ConnectFourState{
	public:
		ConnectFourState();
		ConnectFourState(Player winner);
		ConnectFourState(std::vector<std::vector<Player>> board, Player turn);
		~ConnectFourState();
		
		void setBoard(std::vector<std::vector<Player>> board);
		void setPlayerTurn(Player p);
		std::string displayState() const;
		std::vector<ConnectFourState> getAllPossibleStates();
		bool gameOver();

		friend std::ostream& operator<<(std::ostream& os, const ConnectFourState &state);

		std::vector<std::vector<Player>> _board;
		Player _playerTurn;
		Player _winner;
};


class ConnectFour {
	public:
		ConnectFour(int rows = 6, int cols = 7);
		~ConnectFour();
		std::string displayBoard();

		bool playMove(int col);
		bool checkWin();
		ConnectFourState getGameState();
		void setGameState(ConnectFourState s);
		Player getWinner() {
			return _winner;
		}

	private:
		int _rows;
		int _cols;

		std::vector<std::vector<Player>> _board;
		Player _currentPlayer;
		Player _winner;

		ConnectFourState _state;

		std::string _btmHeader;
};

