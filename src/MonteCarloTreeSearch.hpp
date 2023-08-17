#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <chrono>

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

			// Change ?
			_allPossibleStates = _state.getAllPossibleStates();
			_possibleNextStates = _allPossibleStates.size();
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

		void getAllPossibleStates() {

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
		std::vector<State> _allPossibleStates;

		double _possibleNextStates;
		double _totalNumSim;
		double _winNumSim;
		const double _explorationParameter = sqrt(2);
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

		}

		double simulation(Node<State> *node);

		void backpropogation(Node<State> *node, double result);
		
	private:
		Node<State> *_root;

		const double _timeParameter = 10000; 

};


