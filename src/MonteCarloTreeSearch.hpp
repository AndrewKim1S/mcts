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

			_unexpandedStates = _state.getAllPossibleStates();
			_possibleNextStates = _unexpandedStates.size();
		}

		~Node() {
			for(Node* child : _children) {
				delete child;
			}
		}

		/* Get the UCT Score of the Node */
		double UCTScore() {
			double winRate = (_totalNumSim == 0) ? 0 : _winNumSim/_totalNumSim;
			double sp = (_parent == nullptr) ? 0 : _parent->_totalNumSim;
			double explorationTerm = (sp == 0) ? 0 : 
				_explorationParameter * sqrt(log(sp)/_totalNumSim);
			return winRate + explorationTerm;
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

		
		State _state;
		Node *_parent;
		std::vector<Node*> _children;
		std::vector<State> _unexpandedStates;

		double _possibleNextStates;
		double _totalNumSim;
		double _winNumSim;
		double _explorationParameter = sqrt(2);
};


/* MCTS class */
template<class State>
class MonteCarloTreeSearch {
	
	public:
		MonteCarloTreeSearch() {}
		
		MonteCarloTreeSearch(Node<State> *root) {
			_root = root;
		}
		
		~MonteCarloTreeSearch() {}
	
		/* Run a monte carlo search for the next best move */
		void runSearch() {
			Node<State> *selectedNode = selection(_root);
			std::cout << selectedNode->_state << std::endl;
			
			Node<State> *expandedNode = expansion(selectedNode);
			std::cout << expandedNode->_state << std::endl;
			/*
			auto start = std::chrono::system_clock::now();
			while(std::chrono::system_clock::now() - start < _timeParameter) {
			*/	/*
				Node *selectedNode = selection(_root);
				Node *expandedNode = expansion(selectedNode);
				double simulationResult = simulation(expandedNode);
				backpropogation(expandedNode, simulationResult);
				*/
		//	}
		}

		/* Find a leaf node with the best UCT score */
		Node<State>* selection(Node<State> *rootNode) {
			Node<State> *current = rootNode;
			while(!current->isLeaf() && current->fullyExpanded()) {

				double bestUCT = -1.0;
				Node<State> *bestChild = nullptr;
				for(size_t i = 0; i < current->_children.size(); i++) {
					if(current->_children[i]->UCTScore() > bestUCT) {
						bestUCT = current->_children[i]->UCTScore();
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
		double simulation(Node<State> *node);

		void backpropogation(Node<State> *node, double result);
		
		friend std::ostream& operator<<(std::ostream& os, const ConnectFourState &state);
		
	private:
		Node<State> *_root;

		const double _timeParameter = 10000; 

};


