#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <unordered_map>
//#include <boost/container_hash/hash.hpp>
using namespace std;

struct vertex {
	//both vertex arrays have a list of of the vertex label values not index
	vector<int> outgoing_vertex;
	vector<int> incoming_vertex;
	int group;
};
void DFS_1(const vector<vertex>& vertex_arr, unsigned index, vector<bool>& explored_arr, vector<int>& finishing_time);
int DFS_2(vector<vertex>& vertex_arr, unsigned index, vector<bool>& explored_arr,const  int& group);
int vertex_index(int vertex_number);
//The goal is given an list of clauses. Determine if there is a the constraints are satisfiable 
//The input is a list of clauses of form x1 -x2 represent (x1 + ~x2)
//Output if the constraint is satisfiable
//This programming assignment does not require outputting specific variables that would satisfy the constraint. 
//This is can be done by checking the group numbers of A, ~A and setting the one with the lower group number to be true
//This is because the lower group number corresponds to a lower topological order. It is possible A -> ~A in a satisfiable constraint or vice versa. 
//It is important than to pick the ~A or A based on their topological ordering 
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\2SAT_6.txt", fstream::in);
	int n_variables;
	//Variables will be represent by its number multiplied by -2 - 1 if neg and *2 and -2 for positive, -3 refers to A[6], 3 refers to A[5]
	//-1 = A[1], 1 = A[0]
	vector<vertex> vertex_arr;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> n_variables;
		vertex_arr.resize(2*n_variables);
		int varA;
		int varB;
		int i = 0;
		while (getline(myfile, line)) {
			stringstream ss(line);
			ss >> varA;
			ss >> varB;
			//~A -> B
			vertex_arr[vertex_index(-varA)].outgoing_vertex.push_back(vertex_index(varB));
			//-B -> A 
			vertex_arr[vertex_index(-varB)].outgoing_vertex.push_back(vertex_index(varA));
			//B -> ~A reversed graph
			vertex_arr[vertex_index(varB)].incoming_vertex.push_back(vertex_index(-varA));
			//A-> ~B reversed graph
			vertex_arr[vertex_index(varA)].incoming_vertex.push_back(vertex_index(-varB));
		}
		myfile.close();
	}
	cout << "finished reading input" << endl;
	//first DFS is to find the finishing times in the reverse graph
	vector<bool> explored_arr(vertex_arr.size(), 0);
	vector<int> finishing_time;
	for (unsigned i = 0; i < vertex_arr.size(); i++) {
		if (explored_arr[i] == 0) {
			//cout << "about to explore i =" << i << endl;
			DFS_1(vertex_arr, i, explored_arr, finishing_time);
		}
	}
	cout << "finished first DFS" << endl;
	unsigned start_index;
	vector<bool> explored_arr_1(vertex_arr.size(), 0);
	int group = 1;
	//Second DFS computes the SCC and indicates a group id to each vertex
	for (int i = vertex_arr.size() - 1; i >= 0; i--) {
		//cout << "reached here" << endl;	
		unsigned size = 0;
		start_index = finishing_time[i] - 1;
		if (start_index <0 || start_index > vertex_arr.size() - 1) cout << "ERROR index out of bounds, index = " << start_index << endl;
		if (explored_arr_1[start_index] == 0) {
			size = DFS_2(vertex_arr, start_index, explored_arr_1, group);
			group++;
			//cout << "value of size = " << size<<endl;
		}
	}
	//check that A.group != ~A.group (not in the same SCC)
	for (int i = 1; i <= n_variables; i++) {
		int varA = vertex_index(i);
		int varAbar = vertex_index(-i);
		if (vertex_arr[varA].group == vertex_arr[varAbar].group) {
			cout << "not satisfiable" << endl;
			return 0;
		}
	}
	cout << "satisfiable" << endl;
	
}
int vertex_index(int vertex_number) {
	if (vertex_number < 0) return (vertex_number * -2) - 1;
	else return (vertex_number * 2) - 2;
}
void DFS_1(const vector<vertex>& vertex_arr, unsigned index, vector<bool>& explored_arr, vector<int>& finishing_time) {
	//set vertex index to explored
	explored_arr[index] = 1;
	for (unsigned i = 0; i < vertex_arr[index].incoming_vertex.size(); i++) {
		int incoming_index = vertex_arr[index].incoming_vertex[i];
		if (explored_arr[incoming_index] == 0) {
			//recursively call that vertex to explore
			DFS_1(vertex_arr, incoming_index, explored_arr, finishing_time);
		}
	}
	//once DFS returns all the way back to starting node, push_back its values to the finish array
	finishing_time.push_back(index + 1);
	return;
}
int DFS_2(vector<vertex>& vertex_arr, unsigned index, vector<bool>& explored_arr, const int &group) {
	int count = 1;
	//set vertex index to explored
	explored_arr[index] = 1;
	vertex_arr[index].group = group;
	for (unsigned i = 0; i < vertex_arr[index].outgoing_vertex.size(); i++) {
		int outgoing_index = vertex_arr[index].outgoing_vertex[i];
		if (explored_arr[outgoing_index] == 0) {
			//recursively call that vertex to explore
			count += DFS_2(vertex_arr, outgoing_index, explored_arr,group);
		}
	}
	return count;
}