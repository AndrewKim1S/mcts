#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime>

// add games
#include "ConnectFour.h"


/* Node class */
template<class State>
class Node {

	public:
		Node(Node *parent, State state) {
			_parent = parent;
			_state = state;

			_totalNumSim = 0;
			_winNumSim = 0;
			_uctScore = 0;

			_unexpandedStates = _state.getAllPossibleStates();
			_possibleNextStates = _unexpandedStates.size();
		}

		~Node() {
			for(Node* child : _children) {
				delete child;
			}
		}

		/* Get the UCT Score of the Node */
		double getUCTScore() {
			return _uctScore;
		}

		void updateUCTScore(double win) {
			_totalNumSim ++;
			_winNumSim += win;
			double winRate = (_totalNumSim == 0) ? 0 : _winNumSim/_totalNumSim;
			double sp = (_parent == nullptr) ? 0 : _parent->_totalNumSim;
			double explorationTerm = (sp == 0) ? 0 : 
				_explorationParameter * sqrt(log(sp)/_totalNumSim);
			_uctScore = winRate + explorationTerm;
		}

		/* Add a new child of potential next state */
		Node<State>* getNewChild() {
			if(_unexpandedStates.size() == 0) {
				return nullptr;
			}
			size_t randIndex = rand()%_unexpandedStates.size();
			State possibleState = _unexpandedStates[randIndex];
			_unexpandedStates.erase(_unexpandedStates.begin() + randIndex);
			Node<State> *c = new Node<State>(this, possibleState);
			_children.push_back(c);
			return c;
		}

		bool isLeaf() {
			return _children.size() == 0;
		}

		bool fullyExpanded() {
			return _possibleNextStates == _children.size();
		}

		/* text representation of node */
		friend std::ostream& operator<<(std::ostream& os, const Node<State> &n) { 
			os << n._state;
			os << "\nUCT Score: ";
			os << n._uctScore;
			os << "\n";
			return os;
		}

		State _state;
		Node *_parent;
		std::vector<Node*> _children;
		std::vector<State> _unexpandedStates;

		double _possibleNextStates;
		double _totalNumSim;
		double _winNumSim;
		double _explorationParameter = sqrt(2);
		double _uctScore;
};


/* MCTS class */
template<class State>
class MonteCarloTreeSearch {
	
	public:
		MonteCarloTreeSearch() {}
		
		MonteCarloTreeSearch(Node<State> *root, State winner, State loser) {
			_root = new Node<State>(nullptr, root->_state);
			_winning = winner;
			_losing = loser;
		}
		
		~MonteCarloTreeSearch() {
			delete _root;
		}
	
		/* Run a monte carlo search for the next best move */
		void runSearch() {
			auto start = std::chrono::high_resolution_clock::now();
			int iteration = 0;

			while(true) {
				Node<State> *selectedNode = selection(_root);
				Node<State> *expandedNode = expansion(selectedNode);
				double simulationResult = simulation(expandedNode);
				backpropogation(expandedNode, simulationResult);

				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<double> elapsed = end - start;
				if(elapsed.count() > 15){
					break;
				}
				iteration ++;
			}

			std::cout << iteration << " simulations were considered" << std::endl;
		}

		/* Find a leaf node with the best UCT score */
		Node<State>* selection(Node<State> *rootNode) {
			Node<State> *current = rootNode;
			while(!current->isLeaf() && current->fullyExpanded()) {

				double bestUCT = -1.0;
				Node<State> *bestChild = nullptr;
				for(size_t i = 0; i < current->_children.size(); i++) {
					if(current->_children[i]->getUCTScore() > bestUCT) {
						bestUCT = current->_children[i]->getUCTScore();
						bestChild = current->_children[i];
					}
				}
				current = bestChild;
			}
			return current;
		}

		/* Expand the selected node by creating a child node */
		Node<State>* expansion(Node<State> *node) {
			return node->getNewChild();
		}

		/* Simulate the node until an endgame state is reached */
		double simulation(Node<State> *node) {
			State gameState = node->_state;
			while(!gameState.gameOver()) {
				auto options = gameState.getAllPossibleStates();

				if(options.size() == 0) {
					return 0.0;
				}
				int index = rand()%options.size();
				gameState = options[index];
			}

			if(_winning._winner == gameState._winner) { return 1; }
			else if(_losing._winner == gameState._winner) { return -1; }
			return 0;
		}

		/* Backpropogate the result to the current root of the tree */
		void backpropogation(Node<State> *node, double result) {
			Node<State> *current = node;
			while(current != nullptr) {
				current->updateUCTScore(result);
				current = current->_parent;
			}
		}

		/* Get the node with the highest UCT score */
		State playBestState() {
			Node<State> *bestMove;
			double bestScore = 0.0;
			for(Node<State>* child : _root->_children) {
				if((child->_winNumSim/child->_totalNumSim) > bestScore) {
					bestScore = child->getUCTScore();
					bestMove = child;
				}
			}
			std::cout << "Best Node simulation: " << bestMove->_winNumSim/bestMove->_totalNumSim << std::endl;
			return bestMove->_state;
		}

		/* Get the current state of the game */
		void getCurrentGameState(State s) {
			delete _root;
			_root = new Node<State>(nullptr,s);
		}

	private:
		Node<State> *_root;
		State _winning;
		State _losing;

		double _timeParameter = 10000; 


};


