#pragma once

#include <iostream>
#include <vector>

// Abstract class for a game state
class GameState {
	public:
		virtual std::vector<GameState> getPossibleStates();
		virtual void print(std::ostream &out) const;
};

