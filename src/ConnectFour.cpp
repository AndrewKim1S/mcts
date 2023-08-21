#include "ConnectFour.h"

/* Connect Four State implementation */
ConnectFourState::ConnectFourState() {}


ConnectFourState::ConnectFourState(Player winner) {
	_winner = winner;
}


ConnectFourState::ConnectFourState(std::vector<std::vector<Player>> board, Player turn) {
	_board = board;
	_playerTurn = turn;
	_winner = Player::NONE;
}


ConnectFourState::~ConnectFourState() {}


void ConnectFourState::setBoard(std::vector<std::vector<Player>> board) {
	_board = board;
}


void ConnectFourState::setPlayerTurn(Player p) {
	_playerTurn = p;
}


std::string ConnectFourState::displayState() const {
	std::string board = "";
	size_t rows = _board.size();
	size_t cols = _board[0].size();
	for(size_t i = 0; i < rows; ++i) {
		for(size_t j = 0; j < cols; ++j) {
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
	board+= (_playerTurn == Player::PLAYER_X) ? "Player: X" : "Player: O";
	return board;
}


std::vector<ConnectFourState> ConnectFourState::getAllPossibleStates() {
	std::vector<ConnectFourState> options;
	for(size_t col = 0; col < _board[0].size(); col++) {
		auto copyBoard = _board;
		for(int i = _board.size()-1; i >= 0; --i) {
			if(_board[i][col] == Player::NONE) {
				copyBoard[i][col] = _playerTurn;
				Player nextPlayer = (_playerTurn == Player::PLAYER_X) ? 
					Player::PLAYER_O : Player::PLAYER_X;
				options.push_back(ConnectFourState(copyBoard, nextPlayer));
				break;
			}
		}
	}
	return options;
}


bool ConnectFourState::gameOver() {
	int _rows = _board.size();
	int _cols = _board[0].size();
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


std::ostream& operator<<(std::ostream& os, const ConnectFourState &state) {
	os << state.displayState();
	return os;
}


/* Connect Four game implementation */
ConnectFour::ConnectFour(int rows, int cols) {
	_rows = (rows < 4) ? 4 : rows;
	_cols = (cols < 4) ? 4 : cols;
	_board.resize(rows, std::vector<Player>(cols, Player::NONE));
	_currentPlayer = Player::PLAYER_X;
	_winner = Player::NONE;
	_state = ConnectFourState(_board, _currentPlayer);

	_btmHeader = "";
	for(int i = 0; i <= _rows; ++i) {
		_btmHeader += " " + std::to_string(i);
	}
	_btmHeader += "\n";
}


ConnectFour::~ConnectFour() {}


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
			_state.setBoard(_board);
			_state.setPlayerTurn(_currentPlayer);
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
	return _state;
}

void ConnectFour::setGameState(ConnectFourState s) {
	_currentPlayer = (_currentPlayer == Player::PLAYER_X) ? 
		Player::PLAYER_O : Player::PLAYER_X;
	for(size_t i = 0; i < s._board.size(); i++) {
		for(size_t j = 0; j < s._board[i].size(); j++) {
			_board[i][j] = s._board[i][j];
		}
	}
}
