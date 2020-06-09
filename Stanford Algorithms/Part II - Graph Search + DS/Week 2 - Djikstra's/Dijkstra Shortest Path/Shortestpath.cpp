#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility>

#include "heap.h"
using namespace std;

struct vertex {
	//both vertex arrays have a list of of the vertex label values not index
	vector<pair<int,int>> vertex_length;
	unsigned distance = 9999999;
	
};
void dijkstra_path(vector<vertex>& vertex_arr);
//The goal is to output the sizes of the 5 largest SCC 
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\dijkstra_input.txt", fstream::in);
	//myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SCC_test_cases.txt", fstream::in);
	vector<vertex> vertex_arr;
	int i = 0;
	unsigned label;
	//first populate the array with the number of vertices and outgoing edges
	if (myfile.is_open()) {
		vertex temp_vertex;
		while (getline(myfile, line)) {//loop through input file line by line
			int n;
			vertex_arr.push_back(temp_vertex);
			stringstream ss(line);
			ss >> n;
			pair<int, int> temp(0, 0);
			while (ss >> n) {
				temp.first = n;
				if (ss.peek() == ',') ss.ignore();
				ss >> n;
				temp.second = n;
				vertex_arr[i].vertex_length.push_back(temp);
			}
			i++;
		}
		myfile.close();
	}
	/* Test to check input is read in correctly
	for (int i = 0; i < vertex_arr.size(); i++) {
		cout << "value of i = " << i << endl;
		for (int j = 0; j < vertex_arr[i].vertex_length.size(); j++) {
			cout << "value of outgoing vertex = " << vertex_arr[i].vertex_length[j].first << ", edge length = " << vertex_arr[i].vertex_length[j].second << endl;
		}
	}*/
	dijkstra_path(vertex_arr);
	cout << vertex_arr[6].distance << "," << vertex_arr[36].distance << "," << vertex_arr[58].distance << "," <<
		vertex_arr[81].distance << "," << vertex_arr[98].distance << "," << vertex_arr[114].distance << "," <<
		vertex_arr[132].distance << "," << vertex_arr[164].distance << "," << vertex_arr[187].distance << "," <<
		vertex_arr[196].distance << endl;
	//cout << "value of 113 should be 508, " << vertex_arr[113].distance << endl;
}

void dijkstra_path(vector<vertex> & vertex_arr) {
	vector<bool> explored(vertex_arr.size(), 0);
	unsigned start_index;
	unsigned edge_index;
	int min;

	vertex_arr[0].distance = 0;
	vector<int> temp_dist(200, 9999999999);

	/*HEAP implementation
	heap myheap(temp_dist);
	cout << "value of min = " << myheap.getmin().second<<endl;
	//loop n-1 time until all nodes are explored
	for (int i = 1; i < vertex_arr.size() - 1; i++) {

		pair<int,int> temp = myheap.extractmin();
		int vertex_index = temp.first -1;
		int dist = temp.second;
		//set vertex index to explored
		explored[vertex_index] = 1;
		//set the distance of the vertex
		vertex_arr[vertex_index].distance = dist;
		//add the vertex edges to the heap
		for (int i = 0; i < vertex_arr[vertex_index].vertex_length.size(); i++) {
		}
	}*/
	
	//This is the basic algorithm without a heap
	//start with the edges of 0;
	explored[0] = 1;
	vector<int> finished;
	finished.push_back(0);
	//loop n-1 times until all nodes are explored
	for (int i = 1; i < vertex_arr.size()-1; i++) {
		edge_index = 0;
		start_index = 0;
		min = 9999999999;
		//loop through the explored element's edges
		for (int j = 0; j < finished.size(); j++) {
			//loop through the edge list
			for (int k = 0; k < vertex_arr[finished[j]].vertex_length.size(); k++) {
				//if this vertex is explored, delete edge so we dont look at it again
				int label = vertex_arr[finished[j]].vertex_length[k].first;
				int length = vertex_arr[finished[j]].vertex_length[k].second + vertex_arr[finished[j]].distance;
				if (explored[label - 1] == 1) {
					vertex_arr[finished[j]].vertex_length.erase(vertex_arr[finished[j]].vertex_length.begin() + k);
					k--;
					continue;
				}
				if (length < min) {
					min = length;
					edge_index = k;
					start_index = finished[j];
				}
			}
		}
		
		//found the smallest vertex edges[j]
		int vertex_index = vertex_arr[start_index].vertex_length[edge_index].first - 1;
		//set the vertex to explored
		explored[vertex_index] = 1;
		//set the vertexes distance
		vertex_arr[vertex_index].distance = min;
		//add the vertex to finished array to look at its edges in next loop
		finished.push_back(vertex_index);
	}
	return;
}



