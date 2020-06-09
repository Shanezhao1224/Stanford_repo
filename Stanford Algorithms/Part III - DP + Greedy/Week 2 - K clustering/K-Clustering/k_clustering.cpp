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
struct edge {
	int vertex_a = 0;
	int vertex_b = 0;
	unsigned int length =0;
};

int find(vector<pair<int, int>>& union_ds, int index);
void union_op(vector<pair<int, int>>& union_ds, int index_a, int index_b);
bool edge_comp(edge i, edge j) { 
	return i.length < j.length;
}
//The goal of the code is to find the max spacing k-cluster
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\K_clustering.txt", fstream::in);
	//myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\cluster_test_cases.txt", fstream::in); 
	vector<edge> edge_arr;
	//input file is a list of edges with start/end vertex and length
	int n = 0;
	edge temp;
	int i = 0;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> n;
		int vertex_a_label;
		int vertex_b_label;
		int length;
		while (getline(myfile, line)) {//loop through input file
			stringstream ss(line);
			ss >> vertex_a_label;
			ss >> vertex_b_label;
			ss >> length;
			edge_arr.push_back(temp);
			edge_arr[i].length = length;
			edge_arr[i].vertex_a = vertex_a_label - 1;
			edge_arr[i].vertex_b = vertex_b_label - 1;
			//cout << "value of edge a = " << edge_arr[i].vertex_a << ", value of edge b = " << edge_arr[i].vertex_b << endl;
			//cout << "value of length = " << edge_arr[i].length << endl;
			i++;
		}
		myfile.close();
	}

	/*for (int loop = 0; loop < edge_arr.size(); loop++) {
		cout << "value of vertex_a = " << edge_arr[loop].vertex_a << ", value of vertex_b = " << edge_arr[loop].vertex_b << endl;
		cout << "value of length = " << edge_arr[loop].length << endl;
	}*/
	//sort array of edges
	sort(edge_arr.begin(), edge_arr.end(),edge_comp);
	//check edges are sorted
	for (int loop = 0; loop < edge_arr.size()-1; loop++) {
		if (edge_arr[loop].length > edge_arr[loop + 1].length) {
			cout << "array not sorted correctly" << endl;
		}
		if (edge_arr[loop].vertex_a >= 500 || edge_arr[loop].vertex_b >= 500) {
			cout << "value of vertex_a = "<< edge_arr[loop].vertex_a << ", value of vertex_b = " <<edge_arr[loop].vertex_b << endl;
		}
	}
	cout << "finished sorting" << endl;
	//create an array for vertex and maintain it as a union-find DS
	vector<pair<int, int>> union_find_vertex(n);
	for (unsigned int i = 0; i < union_find_vertex.size(); i++) {
		//initialize all nodes in the union-find to point to itself and have rank 0
		pair<int, int> temp (i, 0);
		union_find_vertex[i] = temp;
	}
	for (int loop = 0; loop < union_find_vertex.size() - 1; loop++) {
		if (union_find_vertex[loop].first != loop || union_find_vertex[loop].second != 0) {
			cout << "union array initialized wrong" << endl;
		}

	}
	int k = 4;
	//loop some amount of times until there are only k clusters
	int j = 0;
	int count = 0;
	while (count < n - k) {
		int index_a = edge_arr[j].vertex_a;
		int index_b = edge_arr[j].vertex_b;
		//check if there is a cycle
		if (find(union_find_vertex, index_a) != find(union_find_vertex, index_b)) {//no cycle
			count++;
			union_op(union_find_vertex, index_a, index_b);
		}
		j++;
	}
	//loop through until we find an edge that is crosses clusters
	while (j < edge_arr.size()) {
		int index_a = edge_arr[j].vertex_a;
		int index_b = edge_arr[j].vertex_b;
		if (find(union_find_vertex, index_a) != find(union_find_vertex, index_b)) {//no cycle
			cout << "max spacing = " << edge_arr[j].length << endl;
			break;
		}
		j++;
	}
	

}

//the following is the implementation of lazy union, path compression algorithms
int find(vector<pair<int, int>>& union_ds,  int index) {
	if (union_ds[index].first == index) {
		return index;
	}
	else {
		//recursively chain up to parent and path compression on return
		union_ds[index].first = find(union_ds, union_ds[index].first);
		return union_ds[index].first;
	}
}
void union_op(vector<pair<int, int>>& union_ds, int index_a,   int index_b) {
	int parent_a = find(union_ds, index_a);
	int parent_b = find(union_ds, index_b);
	//if ranks are equal
	if (union_ds[parent_a].second == union_ds[parent_b].second) {
		//set b to point to a and increment a's rank
		union_ds[parent_b].first = parent_a;
		union_ds[parent_a].second++;
	}
	else if (union_ds[parent_a].second > union_ds[parent_b].second){
		//set b to point to a
		union_ds[parent_b].first = parent_a;

	}
	else {
		//set a to point to b
		union_ds[parent_a].first = parent_b;
	}
	return;
}



