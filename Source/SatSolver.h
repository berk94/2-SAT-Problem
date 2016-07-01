/*
 * SatSolver.h
 *
 *  Created on: Nov 30, 2014
 *      Author: Kemal Berk Kocabagli
 */
#ifndef SATSOLVER_H_
#define SATSOLVER_H_

#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//represents a node
struct Node {
	int vertex; //value of this node
	int index; //index of traversal of this node
	int lowlink; //index of the root of the scc in which this node is found
	int TV=-1; //truth value of this node, not yet determined
	bool inStack; //whether this node is in (the) stack or not

	vector <Node*> nb; //the list that holds all the neighbors of this node
	Node(int v) {
		index= -1; //not yet traversed
		lowlink= -1;
		vertex = v;
		inStack = false;
	}
	bool operator<( const Node& val ) const {
	    	return vertex < val.vertex;
	    }

};
class SatSolver{
private:
	vector<Node*> adjList; //the list of nodes in the graph given to this SatSolver 
public:
  // Reads the input file and creates the adjacency list
  SatSolver(std::string filename);

  // Outputs the adjacency list to the file
  void Part1(std::string filename);

  // Finds the strongly connected components and outputs them to the file
  void Part2(std::string filename);
  void Scc(Node* n);

  // Assigns the truth values of the prepositions and outputs the assignments to the file
  void Part3(std::string filename);

};

#endif
