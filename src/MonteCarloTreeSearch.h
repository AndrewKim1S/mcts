// https://medium.com/@quasimik/monte-carlo-tree-search-applied-to-letterpress-34f41c86e238
#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "GameState.h"

// Node 
struct Node {
	Node(Node *parent, GameState state) {
		_parent = parent;
		_state = state;

		_totalNumSim = 0;
		_winNumSim = 0;
	}

	~Node() {
		delete _parent;
		for(auto &n : _children) {
			delete n;
		}
	}

	double UCTScore() {
		double winRate = (_totalNumSim = 0) ? 0 : _winNumSim/_totalNumSim;
		double sp = _parent->_totalNumSim;
		double explorationTerm = (sp = 0) ? 0 : 
			_explorationParameter * sqrt(log(sp)/_totalNumSim);
		return winRate + explorationTerm;
	}

	GameState _state;
	Node *_parent;
	std::vector<Node*> _children;
	
	double _totalNumSim;
	double _winNumSim;
	const double _explorationParameter = sqrt(2);
};


// MCTS 
class MonteCarloTreeSearch {
	public:
		MonteCarloTreeSearch(Node *root);
		~MonteCarloTreeSearch();
		
		void runSearch();
		Node* selection(Node *currentNode);
		Node* expansion(Node *node);
		double simulation(Node *node);
		void backpropogation(Node *node, double result);
		
	private:
		Node *_root;

};

