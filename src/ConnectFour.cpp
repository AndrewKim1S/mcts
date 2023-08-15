#include "ConnectFour.h"

ConnectFour::ConnectFour(int rows, int cols) {
	_rows = (rows < 4) ? 4 : rows;
	_cols = (cols < 4) ? 4 : cols;
	_board.resize(rows, std::vector<Player>(cols, Player::NONE));
	_currentPlayer = Player::PLAYER_X;
	_winner = Player::NONE;

	_btmHeader = "";
	for(int i = 0; i <= _rows; ++i) {
		_btmHeader += " " + std::to_string(i);
	}
	_btmHeader += "\n";
}

ConnectFour::~ConnectFour() {

}

std::string ConnectFour::displayBoard() {
	std::string board = "";
	for(int i = 0; i < _rows; ++i) {
		for(int j = 0; j < _cols; ++j) {
			switch(_board[i][j]) {
				case Player::PLAYER_X:
					board += "|X";
					break;
				case Player::PLAYER_O:
					board += "|O";
					break;
				default:
					board += "| ";
			}
		}
		board += "|\n";
	}
	
	board += _btmHeader;
	return board;
}

bool ConnectFour::playMove(int col) {
	if(col < 0 || col >= _cols) {
		std::cout << "Invalid Column" << std::endl;
		return false;
	}
	for(int i = _rows -1; i >= 0; --i) {
		if(_board[i][col] == Player::NONE) {
			_board[i][col] = _currentPlayer;
			_currentPlayer = (_currentPlayer == Player::PLAYER_X) ? 
				Player::PLAYER_O : Player::PLAYER_X;
			return true;
		}
	}
	std::cout << "column is full" << std::endl;
	return false;
}

bool ConnectFour::checkWin() {
	for(int i = 0; i < _rows; ++i) {
		for(int j = 0; j <= _cols -4; ++j) {
			auto x = _board[i][j];
			if(x != Player::NONE 
				&& _board[i][j+1] == x && _board[i][j+2] == x && _board[i][j+3] == x) {
				_winner = x;
				return true;
			}
		}
	}
	
	for(int i = 0; i <= _rows-4; ++i) {
		for(int j = 0; j < _cols; ++j) {
			auto x = _board[i][j];
			if(x != Player::NONE 
				&& _board[i+1][j] == x && _board[i+2][j] == x && _board[i+3][j] == x) {
				_winner = x;
				return true;
			}
		}
	}

	for(int i = 0; i <= _rows-4; ++i) {
		for(int j = 0; j <= _cols-4; ++j) {
			auto x = _board[i][j];
			if(x!=Player::NONE && _board[i+1][j+1] == x && _board[i+2][j+2] == x &&
				_board[i+3][j+3] == x) {
				_winner = x;
				return true;
			}
			x = _board[i][j+3];
			if(x!=Player::NONE && _board[i+1][j+2] == x && _board[i+2][j+1] == x &&
				_board[i+3][j] == x) {
				_winner = x;
				return true;
			}
		}
	}

	return false;
}

ConnectFourState ConnectFour::getGameState() {

}
