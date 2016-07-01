/*
 * SatSolver.cc
 *
 *  Created on: Nov 30, 2014
 *      Author: Kemal Berk Kocabagli
 */
#include "SatSolver.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stack>
using namespace std;

int no_of_var; // number of vertices
int no_of_couples; // number of couples
int counter=0; // counter for graph traversal
stack <Node*> s; // the stack filled and emptied while building the SCCs
bool twoSAT=true; // whether this problem is 2-satisfiable or not
vector < vector<Node*> > sccList; // the list that holds every SCC

SatSolver::SatSolver(std::string filename){
ifstream myFile(filename);

	while (myFile.good()){
		string line;
		int l=1;
		while (getline (myFile, line)) {
			//cout << "reading line" << l << endl;
			stringstream ss;
			ss<<line;
			if (l==1){ 
				ss >> no_of_var;
				ss >> no_of_couples;
				for (int i=-no_of_var;i<=no_of_var ;i++){
					if (i!=0){
						Node* n= new Node(i);
						adjList.push_back(n);
					}
				}
				l++;
			}
			else {  //read the connections and form the adj list
				l++;
				int source;
				int dest;
				ss >> source;
				ss >> dest;
				int dev1=no_of_var;
				int dev2=dev1-1;
				int destloc=dest+dev2;
				int sourceloc= source +dev2;
				if (source>0){
					if(dest<0) destloc++;
					adjList[-source+dev1]->nb.push_back(adjList[destloc]);
				}
				else if (source<0)
				{if(dest<0) destloc++;
				adjList[-source+dev2]->nb.push_back(adjList[destloc]);}

				if (dest>0){
					if(source<0) sourceloc++;
					adjList[-dest+dev1]->nb.push_back(adjList[sourceloc]);
				}
				else if (dest<0)
				{if(source<0) sourceloc++;
				adjList[-dest+dev2]->nb.push_back(adjList[sourceloc]);
				}
			}
		}
	}
}


void SatSolver::Part1(std::string filename){
ofstream outPut;
outPut.open(filename.c_str()); //create output file
for (int i=0; i<adjList.size(); i++){
		Node* current = adjList[i];
		outPut << current->vertex;
		for (int j=0; j<current->nb.size(); j++)
			outPut << " " << current->nb[j]->vertex;
		outPut << endl;
	}
}

//TARJAN'S Algorithm to find the strongly connected component(SCC)s
void SatSolver::Part2(std::string filename){
ofstream outPut;
outPut.open(filename.c_str()); //create output file
	for (Node* n: adjList){
		if(n->index==-1) //node not visited
		{//cout << "traversing node "<< n->vertex <<endl;
			Scc(n);}
	}
	for (int i=sccList.size()-1; i>=0; i--){
			for (Node* p: sccList[i]){
			outPut << p->vertex << " ";
		}
	outPut << endl;
	}
}

void SatSolver::Scc(Node *n){
n->index = counter;
	n->lowlink = counter;
	counter++;
	s.push(n);
	//cout << "node " << n->vertex << " pushed in stack" << endl;
	//cout << "index of " << n->vertex << ":" << n->index<< endl;
	n->inStack= true;
	//cout << "is node " << n->vertex << " in stack:" << n->inStack << endl ;
	//go to the neighbors of n
	for(Node* child: n->nb){
		if(child->index==-1){ //child not visited yet
			Scc(child);	// recursive call on child (dfs)
			n->lowlink= min(n->lowlink, child->lowlink);
		}
		else if (child->inStack){ //child already in stack, so it is closer to the root than the current node
			n->lowlink = min(n->lowlink, child->index);
		}
	}
	if (n->lowlink == n->index){ //ROOT FOUND!!
		vector<Node*> scc;
		//cout <<"SCC DETECTED!!!!!" << "lowlink" << n->lowlink << endl;
		while (!s.empty()){
			Node* scc_element =s.top();
			scc_element->inStack=false;
			//cout << "element popped: " <<scc_element->vertex << " ";
			s.pop();
			scc.push_back(scc_element);

			if(n->index==scc_element->index) {
				break;
			}
		}

		//cout << "SCC!!!!!!!!!!!!!!!!!!!!!" <<endl;
		sort(scc.begin(), scc.end());
		sccList.insert(sccList.begin(),scc);

		if(twoSAT){

		//CHECK if the recently found SCC has Xj and -Xj to decide if the problem is 2-SAT
		int check[no_of_var];
		fill_n(check, no_of_var, 0);
		for (Node* p: scc){
			check[abs(p->vertex)-1]++;
		}
		for(int i:check){
			//cout << i ;
			if(i>1) {
				twoSAT=false; //i>1 (max 2) means that Xj and -Xj are in the current, same SCC
				break;
			}
		}

		}

	}

}


void SatSolver::Part3(std::string filename){
ofstream outPut;
outPut.open(filename.c_str()); //create output file
if(twoSAT) {

		for (vector <Node*> scc: sccList){  //Assign the truth values
			for (Node* p: scc){
				if(p->TV==-1){
					p->TV=0;
					int notp= -p->vertex;
					if(notp<0)
						adjList[notp+no_of_var]->TV=1;
					else
						adjList[notp+no_of_var-1]->TV=1;
				}
			}
		}
		outPut << adjList[no_of_var]->TV;
		for(int i=no_of_var+1;i<adjList.size(); i++){
			outPut << " " <<adjList[i]->TV;
		}
		outPut<<endl;
}
else{
		outPut <<"-1" << endl;
    }

}