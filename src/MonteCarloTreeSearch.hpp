#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>
#include <ctime>

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
			os << "\nUCT Score: " ;
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
		
		MonteCarloTreeSearch(Node<State> *root, State winner) {
			_root = root;
			_winning = winner;
		}
		
		~MonteCarloTreeSearch() {}
	
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
				std::chrono::duration<double> elapsed = start - end;
				if(iteration > 500){
					break;
				}
				iteration ++;
			}
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
		// TODO error 
		double simulation(Node<State> *node) {
			State gameState = node->_state;
			while(!gameState.gameOver()) {
				auto options = gameState.getAllPossibleStates();
				gameState = options[rand()%options.size()];
			}
			return _winning._winner == gameState._winner;
		}

		/* Backpropogate the result to the current root of the tree */
		void backpropogation(Node<State> *node, double result) {
			Node<State> *current = node;
			while(current != nullptr) {
				current->updateUCTScore(result);
				current = current->_parent;
			}
		}
	
		/* text representation of mcts */
		friend std::ostream& operator<<(std::ostream& os, const MonteCarloTreeSearch &mcts) {
			return os;	
		}
		
	private:
		Node<State> *_root;
		State _winning;

		double _timeParameter = 10000; 

		

};


