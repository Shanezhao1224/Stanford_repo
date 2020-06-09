#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

struct vertex {
	//both vertex arrays have a list of of the vertex label values not index
	vector<int> outgoing_vertex;
	vector<int> incoming_vertex;
};

void DFS_1(const vector<vertex>& vertex_arr, unsigned index, vector<bool>& explored_arr, vector<int>& finishing_time) {
	//set vertex index to explored
	explored_arr[index] = 1;
	for (unsigned i = 0; i < vertex_arr[index].incoming_vertex.size(); i++) {
		int incoming_label = vertex_arr[index].incoming_vertex[i];
		if (explored_arr[incoming_label -1] == 0) {
			//recursively call that vertex to explore
			DFS_1(vertex_arr, incoming_label - 1, explored_arr, finishing_time);
		}
	}
	//once DFS returns all the way back to starting node, push_back its values to the finish array
	finishing_time.push_back(index + 1);
	return;
}

int DFS_2(const vector<vertex>& vertex_arr, unsigned index, vector<bool>& explored_arr) {
	int count = 1;
	//set vertex index to explored
	explored_arr[index] = 1;
	for (unsigned i = 0; i < vertex_arr[index].outgoing_vertex.size(); i++) {
		int outgoing_label = vertex_arr[index].outgoing_vertex[i];
		if (explored_arr[outgoing_label - 1] == 0) {
			//recursively call that vertex to explore
			count += DFS_2(vertex_arr, outgoing_label - 1, explored_arr);
		}
	}
	return count;
}
void max_5(int& max1, int& max2, int& max3, int& max4, int& max5, int size) {
	max1 = (size > max2) ? max2 : (size > max1) ? size : max1;
	max2 = (size > max3) ? max3 : (size > max2) ? size : max2;
	max3 = (size > max4) ? max4 : (size > max3) ? size : max3;
	max4 = (size > max5) ? max5 : (size > max4) ? size : max4;
	max5 = (size > max5) ? size : max5;
	return;
}
//The goal is to output the sizes of the 5 largest SCC 
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SCC_input.txt", fstream::in);
	//myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SCC_test_cases.txt", fstream::in);
	vector<vertex> vertex_arr;
	int i = 0;
	unsigned label;
	//first populate the array with the number of vertices and outgoing edges
	if (myfile.is_open()) {
		int outgoing_vertex;
		vertex temp;
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream stream(line);
			stream >> label;
			while (label > vertex_arr.size()) { //resize the vertex arr
				vertex_arr.push_back(temp);
			}
			stream >> outgoing_vertex;
			vertex_arr[label - 1].outgoing_vertex.push_back(outgoing_vertex);
		}
		myfile.close();
	}
	//myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SCC_test_cases.txt", fstream::in);
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SCC_input.txt", fstream::in);

	if (myfile.is_open()) {
		int incoming_vertex;
		vertex temp;
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream stream(line);
			stream >> incoming_vertex;
			stream >> label;
			vertex_arr[label - 1].incoming_vertex.push_back(incoming_vertex);
		}
		myfile.close();
	}
	
	/*for (int i = 0; i < vertex_arr.size(); i++) {
		cout << i << "th element edges" << endl;
		for (int j = 0; j < vertex_arr[i].outgoing_vertex.size(); j++) {
			cout << "value of outgoing edge = " << vertex_arr[i].outgoing_vertex[j] << endl;
		}
	}
	for (int i = 0; i < vertex_arr.size(); i++) {
		cout << i << "th element edges" << endl;
		for (int j = 0; j < vertex_arr[i].incoming_vertex.size(); j++) {
			cout << "value of incoming edge = " << vertex_arr[i].incoming_vertex[j] << endl;
		}
	}*/
	
	vector<bool> explored_arr(vertex_arr.size(), 0);
	vector<int> finishing_time;
	//loop through all the vertexes in the reverse direction to find finishing time
	for (unsigned i = 0; i < vertex_arr.size(); i++) {
		if (explored_arr[i] == 0) {
			//cout << "about to explore i =" << i << endl;
			DFS_1(vertex_arr, i, explored_arr, finishing_time);
		}
	}
	explored_arr.clear();
	/*for (unsigned i = 0; i<finishing_time.size(); i++) {
		cout << finishing_time[i]<<" ";
	}*/
	cout << endl;
	vector<bool> explored_arr_1(vertex_arr.size(), 0);	
	unsigned start_index;
	int max1 = 0, max2 = 0, max3 = 0, max4 = 0, max5 = 0;
	//second dfs loop

	for (int i = vertex_arr.size()-1; i >= 0; i--) {
		//cout << "reached here" << endl;	
		unsigned size = 0;
		start_index = finishing_time[i] -1;
		if (explored_arr_1[start_index] == 0) {
			size = DFS_2(vertex_arr, start_index, explored_arr_1);
			//cout << "value of size = " << size<<endl;
		}
		//compare size to the five "max" variables
		max_5(max1, max2, max3, max4, max5, size);
	}
	cout <<max5 << "," << max4 << "," << max3 << "," << max2 << "," << max1 << endl;;
}


