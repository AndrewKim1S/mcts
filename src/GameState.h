#include <iostream>
#include <vector>

struct GameState {

	virtual std::vector<GameState> getPossibleStates();
};

struct ConnectFourState : GameState {
	void test() {
		std::cout << "test" << std::endl;
	}
};
