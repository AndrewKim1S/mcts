#include "MonteCarloTreeSearch.h"

MonteCarloTreeSearch::MonteCarloTreeSearch(Node *root) {
	_root = root;
}

MonteCarloTreeSearch::~MonteCarloTreeSearch() {
	delete _root;
}

void MonteCarloTreeSearch::runSearch() {
	bool continueSearch = true;
	while(continueSearch) {
		Node *selectedNode = selection(_root);
		Node *expandedNode = expansion(selectedNode);
		double simulationResult = simulation(expandedNode);
		backpropogation(expandedNode, simulationResult);
	}
	
}

Node* MonteCarloTreeSearch::selection(Node *currentNode) {

}

Node* MonteCarloTreeSearch::expansion(Node *node) {

}

double MonteCarloTreeSearch::simulation(Node *node) {

}

void MonteCarloTreeSearch::backpropogation(Node *node, double result) {

}

