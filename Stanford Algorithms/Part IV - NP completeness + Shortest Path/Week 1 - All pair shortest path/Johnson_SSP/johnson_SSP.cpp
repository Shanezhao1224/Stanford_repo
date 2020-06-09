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


using namespace std;

int min(int left, int right);
struct vertex {
	vector<pair<int, int>> incoming_edges;
	vector<pair<int, int>> outgoing_edges;
};
void bellman_ford(vector<vertex>& vertex_arr, vector<vector<int>>& bellman_dp, int &i);
//The goal is given an G with negative edge lengths, compute the shortest (u,v) path
//The input is a list of edges with u, v, edge length
//Output the shortest path distance

//Going to use jonhson's SSP algorith
/****It seems you can get the correct answer with just the bellman-ford part of the johnson algorithm
If the graph has negative edges, the bellman-ford with an extra vertex s returns the smallest path
Inituively all the distances are bounded by 0 and can only decrease by negative edges and since
Bellman-ford looks at each incoming edge and that nodes distance, it should give us the correct minimum distance for any vertex
It seems to be correct and works, but how can Johnson Algorithm even exist if this was indeed true?
***/


int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SSP_big.txt", fstream::in);
	int vertices = 0;
	int edges = 0;
	vector<vertex> vertex_arr;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> vertices;
		ss >> edges;
		vertex_arr.resize(vertices);
		int u;
		int v;
		int length;
		while (getline(myfile, line)) {
			stringstream ss(line);
			ss >> u;
			ss >> v;
			ss >> length;
			//edge arr stores vertex indexes not labels
			vertex_arr[u - 1].outgoing_edges.push_back(make_pair(v - 1, length));
			vertex_arr[v - 1].incoming_edges.push_back(make_pair(u - 1, length));
		}
		myfile.close();
	}
	//add temporary s into graph to calculate weights for reweighting
	vertex s;
	for (int i = 0; i < vertices; i++) {
		s.outgoing_edges.push_back(make_pair(i, 0));
	}
	vertex_arr.push_back(s);
	//initialize the dp arr
	vector<vector<int>> bellman_dp;
	bellman_dp.resize(2);
	for (int i = 0; i < bellman_dp.size(); i++) {
		bellman_dp[i].resize(vertex_arr.size());
		if (i != bellman_dp.size() - 1) {
			bellman_dp[0][i] = 99999999;
		}
		else {
			bellman_dp[0][i] = 0;
		}
		
	}
	//run bellman-ford with s are start vertex
	int i = 1;
	bellman_ford(vertex_arr, bellman_dp, i);
	bool previ = !(i % 2);
	int min = 99999;
	for (int v = 0; v < vertex_arr.size(); v++) {
		int case1 = bellman_dp[previ][v];
		min = case1 < min ? case1 : min;
		int case2 = 9999999;
		//loop through the edges
		for (int j = 0; j < vertex_arr[v].incoming_edges.size(); j++) {
			int in_vertex = vertex_arr[v].incoming_edges[j].first;
			int in_distance = vertex_arr[v].incoming_edges[j].second;
			if (bellman_dp[previ][in_vertex] + in_distance < case2) {
				case2 = bellman_dp[previ][in_vertex] + in_distance;
			}
		}
		if (case2 < case1) {
			goto NEGATIVE_CYCLE;
		}
		else {
		}
	}
	cout << "min = " <<min<< endl;
	return 0;
NEGATIVE_CYCLE:
	cout << "THERE IS A NEGATIVE CYCLE" << endl;
	return 0;
}

void bellman_ford(vector<vertex>& vertex_arr, vector<vector<int>> & bellman_dp,int &i) {
	bool curri = 1;
	bool previ = !curri;
	for (i = 1; i < vertex_arr.size(); i++) {
		//cout << "previ = " << previ << ", curri = " << curri << endl;
		bool changes = false;
		for (int v = 0; v < vertex_arr.size(); v++) {
			int case1 = bellman_dp[previ][v];
			int case2 = 9999999;
			//loop through the edges
			for (int j = 0; j < vertex_arr[v].incoming_edges.size(); j++) {
				int in_vertex = vertex_arr[v].incoming_edges[j].first;
				int in_distance = vertex_arr[v].incoming_edges[j].second;
				if (bellman_dp[previ][in_vertex] + in_distance < case2) {
					case2 = bellman_dp[previ][in_vertex] + in_distance;
				}
			}
			if (case2 < case1) {
				bellman_dp[curri][v] = case2;
				changes = true;
			}
			else {
				bellman_dp[curri][v] = case1;
			}
		}
		if (!changes) {
			cout << "finished early at i = " << i << endl;
			i++;
			break;
		}
		curri = previ;
		previ = !previ;
	}
	return;
}
int min(int left, int right) {
	return left < right ? left : right;
}

/*void dijkstra_path(vector<vertex>& vertex_arr) {
	vector<bool> explored(vertex_arr.size(), 0);
	unsigned start_index;
	unsigned edge_index;
	int min;

	vertex_arr[0].distance = 0;
	vector<int> temp_dist(200, 9999999999);
	
	//This is the basic algorithm without a heap
	//start with the edges of 0;
	explored[0] = 1;
	vector<int> finished;
	finished.push_back(0);
	//loop n-1 times until all nodes are explored
	for (int i = 1; i < vertex_arr.size() - 1; i++) {
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
}*/