#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <functional>

using namespace std;
//#define naive
struct vertex {
	vector<pair<int, int>> edges;
};


//void heapify(vector <pair<int, int>> myheap);
//The goal of the code is to find the MST using Prim's algorithm
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\Prim_mst.txt", fstream::in);
	vector<vertex> vertex_arr;
	//input file is a list of edges with start/end vertex and length
	int n = 0;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> n;
		vertex_arr.resize(n);
		int start_label;
		int end_label;
		int length;
		while (getline(myfile, line)) {//loop through input file
			stringstream ss(line);
			ss >> start_label;
			ss >> end_label;
			ss >> length;
			pair<int, int> edge_start(end_label-1, length);
			pair<int, int> edge_end(start_label-1, length);
			vertex_arr[start_label - 1].edges.push_back(edge_start);
			vertex_arr[end_label - 1].edges.push_back(edge_end);
		}
		myfile.close();
	}
	vector<bool> explored(n, false);
	long long count = 0;
#ifdef naive
	//naive non heap 
	//set the initial distance to be very high
	vector<int> vertex_length(n, 99999999);
	vertex_length[0] = 0;
	for (int i = 0; i < n; i++) {
		int index=0;
		int min = 99999999;
		//find the cheapest vertex;
		for (int j = 0; j < vertex_length.size(); j++) {
			if (vertex_length[j] < min) {
				min = vertex_length[j];
				index = j;
			}
		}
		//set the vertex to large number so you dont pick it again
		vertex_length[index] = 99999999;
		count += min;
		explored[index] = true;
		//update the distances
		for (int j = 0; j < vertex_arr[index].edges.size(); j++){
			int vertex_index = vertex_arr[index].edges[j].first;
			int length = vertex_arr[index].edges[j].second;
			if (!explored[vertex_index]) {
				if (length < vertex_length[vertex_index]) {
					vertex_length[vertex_index] = length;
				}
			}
		}
		cout << "one loop" << endl;
	}

#else
	//comparison function for pair to pass to priority queue
	struct pair_compare {
		bool operator()(const pair<int, int>& temp1, const pair<int, int> &temp2) {
			if (temp1.second > temp2.second) {
				return true;
			}
			else {
				return false;
			}
		}
	};
	
	//priority queue implementation gives us O(mlogm), to get best case of O(mlogn) need a custom heap implementation
	priority_queue <pair<int,int>, vector<pair<int,int>>, pair_compare> min_heap;
	//start with 0
	
	pair<int, int> temp  (0, 0);
	min_heap.push(temp);
	//pair<int, int> temp2(0, 9999999);
	//min_heap.push(temp2);
	cout << "value of min = " << min_heap.top().second <<", size of heap = "<<min_heap.size()<< endl;
	for (int i = 0; i < n; i++) {
		while (explored[min_heap.top().first]) {
			min_heap.pop();
		}
		int vertex_index = min_heap.top().first;
		count += min_heap.top().second;
		min_heap.pop();
		explored[vertex_index] = true;
		for (int j = 0; j < vertex_arr[vertex_index].edges.size(); j++) {
			//this vertex is not explored
			if (!explored[vertex_arr[vertex_index].edges[j].first]) {
				min_heap.push(vertex_arr[vertex_index].edges[j]);
			}
		}
	}

#endif

	for (int i = 0; i < explored.size(); i++) {
		if (!explored[i]) cout << "ERROR: vertex not explored " << endl;
	}
	cout << "value of sum = " << count << endl;
}



