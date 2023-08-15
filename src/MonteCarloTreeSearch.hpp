#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "ConnectFour.h"


// Node 
template<class State>
class Node {

	public:
		Node(Node *parent, State state) {
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

		State _state;
		Node *_parent;
		std::vector<Node*> _children;
		
		double _totalNumSim;
		double _winNumSim;
		const double _explorationParameter = sqrt(2);
};


// MCTS 
template<class State>
class MonteCarloTreeSearch {
	
	public:
		MonteCarloTreeSearch() {

		}
		
		MonteCarloTreeSearch(Node<State> *root) {
			_root = root;
		}
		
		~MonteCarloTreeSearch() {
			// delete _root;
		}
		
		void runSearch() {
			bool continueSearch = true;
			while(continueSearch) {
				/*
				Node *selectedNode = selection(_root);
				Node *expandedNode = expansion(selectedNode);
				double simulationResult = simulation(expandedNode);
				backpropogation(expandedNode, simulationResult);
			*/}
		}

		Node<State>* selection(Node<State> *currentNode);

		Node<State>* expansion(Node<State> *node);

		double simulation(Node<State> *node);

		void backpropogation(Node<State> *node, double result);
		
	private:
		Node<State> *_root;

};


