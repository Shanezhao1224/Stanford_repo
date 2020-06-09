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
	double x;
	double y;
};
double euclidean_distance(vertex a, vertex b);
//Heap functions
void shift_down(vector<pair<double, int>>& heap_arr, vector<int>& heap_key, int index);
void shift_up(vector<pair<double, int>>& heap_arr, vector<int>& heap_key, int heap_index);
pair<double, int> extractmin(vector<pair<double, int>>& heap_arr, vector<int>& heap_key);

//The goal is given an G with vertices as a set of (x,y) coordinates, solve the TSP using a greedy heuristic of traveling to the closest vertex next
//Running time should be O(mlog(n)) 
//The input is a list of vertices with its (x,y) coordinates
//Output minimum cost tour rounded to integer
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\TSP_big.txt", fstream::in);
	int n_vertices = 0;
	vector<vertex> vertex_arr;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> n_vertices;
		vertex_arr.resize(n_vertices);
		double x;
		double y;
		int i = 0;
		while (getline(myfile, line)) {
			stringstream ss(line);
			ss >> x;
			ss >> x;
			ss >> y;
			vertex_arr[i].x = x;
			vertex_arr[i].y = y;
			i++;
		}
		myfile.close();
	}
	cout << "finished reading input" << endl;
	//array for heap implementation
	vector<pair<double, int>> heap_arr(n_vertices);
	//vector to map vertex to index in heap
	vector<int> heap_key(n_vertices);
	//initialize the heap array with distances
	for (int i = 0; i < n_vertices; i++) {
		if (i == 0) heap_arr[i] = make_pair(0, i);
		else heap_arr[i] = make_pair(99999999, i);
		heap_key[i] = i;
	}
	//Heap needs to support change key value (i.e shifting up and down) and extract_min
	vector<bool> explored(n_vertices, false);
	int last = 0;
	double totaldistance = 0;
	for (int i = 0; i < n_vertices; i++) {
		pair<double, int> next_vertex = extractmin(heap_arr, heap_key);
		if (explored[next_vertex.second]) cout << "ERROR vertex "<<next_vertex.second<<" should not be explored!" << endl;
		//cout << "closest vertex = " << next_vertex.second << endl;
		//set the vertex to explored
		explored[next_vertex.second] = true;
		//recalculate the distance for each edge
		for (int j = 0; j < n_vertices; j++) {
			if (explored[j] == true) continue;
			int heap_index = heap_key[j];
			if (heap_index >= heap_arr.size()) {
				cout << "ERROR HEAPINDEX OUT OF BOUNDS for j = " << j<<", index = "<<heap_index << endl;
			}
			//if the new distance is less than the previous distance
			double distance = euclidean_distance(vertex_arr[j], vertex_arr[next_vertex.second]);
			if (distance < heap_arr[heap_index].first) {
				heap_arr[heap_index].first = distance;
				shift_up(heap_arr, heap_key, heap_index);
			}
			else {
				heap_arr[heap_index].first = distance;
				shift_down(heap_arr, heap_key, heap_index);
			}
		}
		//cout<< next_vertex.second +1 << endl;
		totaldistance += next_vertex.first;
		last = next_vertex.second;
	}
	//add the distance of the loop back to itself
	totaldistance += euclidean_distance(vertex_arr[0], vertex_arr[last]);

	cout << "minimum tour is = " << int(totaldistance) << endl;

}
void shift_up(vector<pair<double,int>> & heap_arr,vector<int> & heap_key, int heap_index) {
	if (heap_index <= 0) {
		return;
	}
	int parent = (heap_index - 1) / 2;
	int parent_vertex = heap_arr[parent].second;
	int index_vertex = heap_arr[heap_index].second;
	if (heap_arr[parent].first > heap_arr[heap_index].first) {
		//swap upwards
		swap(heap_arr[parent], heap_arr[heap_index]);
		//change the mapping
		heap_key[parent_vertex] = heap_index;
		heap_key[index_vertex] = parent;
		//recursively shift up 
		shift_up(heap_arr, heap_key, parent);
	}
	else if (heap_arr[parent].first == heap_arr[heap_index].first) {
		if (index_vertex < parent_vertex) {
			//swap upwards
			swap(heap_arr[parent], heap_arr[heap_index]);
			//change the mapping
			heap_key[parent_vertex] = heap_index;
			heap_key[index_vertex] = parent;
			//recursively shift up 
			shift_up(heap_arr, heap_key, parent);
		}
	}
	return;
}
pair<double, int> extractmin(vector<pair<double, int>>& heap_arr, vector<int>& heap_key) {
	pair<double, int> returnpair = heap_arr[0];
	//set the vertex out of bounds since it is being removed
	heap_key[heap_arr[0].second] = 999999;
	heap_key[heap_arr[heap_arr.size()-1].second] = 0;
	//swap the top node with leaf
	swap(heap_arr[0], heap_arr[heap_arr.size() - 1]);
	//remove the last leaf
	heap_arr.erase(heap_arr.begin() + heap_arr.size()-1);
	//shift downwards
	shift_down(heap_arr, heap_key, 0);
	return returnpair;
}
void shift_down(vector<pair<double, int>>& heap_arr, vector<int>& heap_key, int index) {
	int smallest;
	if (index > int(heap_arr.size() / 2) - 1) {
		return;
	}
	int child1 = index * 2 + 1;
	int child2 = index * 2 + 2;
	double child1_distance = heap_arr[child1].first;
	double child2_distance;
	//check if child 2 is out of bounds
	child2_distance = (child2 > int(heap_arr.size()) - 1) ? 9999999 : heap_arr[child2].first;
	
	if (child1_distance > child2_distance) {
		smallest = child2;
	}
	else if (child1_distance < child2_distance) {
		smallest = child1;
	}
	else {//need to break distance ties by vertex number
		if (heap_arr[child1].second < heap_arr[child2].second) {
			smallest = child1;
		}
		else {
			smallest = child2;
		}
	}

	if (heap_arr[index].first < heap_arr[smallest].first) {
		smallest = index;
	}
	else if (heap_arr[index].first == heap_arr[smallest].first){
		if (heap_arr[index].second < heap_arr[smallest].second) {
			smallest = index;
		}
	}
	if (smallest != index) {
		int vertex_parent = heap_arr[index].second;
		int vertex_child = heap_arr[smallest].second;
		//change the mapping
		heap_key[vertex_parent] = smallest;
		heap_key[vertex_child] = index;
		//swap
		swap(heap_arr[index], heap_arr[smallest]);
		//continue shifting down 
		shift_down(heap_arr, heap_key, smallest);
	}
	return;
	
}
double euclidean_distance(vertex a, vertex b) {
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

