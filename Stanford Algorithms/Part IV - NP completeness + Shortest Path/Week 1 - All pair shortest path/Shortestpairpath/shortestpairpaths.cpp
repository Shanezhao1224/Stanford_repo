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
#include <boost/container_hash/hash.hpp>


using namespace std;

int min(int left, int right);
//void floyd_warshall_recurse(unordered_map<string, int>& dp_map, unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>>& edge_map, int u, int v, int k);

//The goal is given an G with negative edge lengths, compute the shortest (u,v) path
//The input is a list of edges with u, v, edge length
//Output the shortest path distance

//Going to use floyd marshall algorith with a recursive top down approach 
//Need hashmap of (u,v) edges to get constant lookup for if there is a path from u to v

int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SSP_3.txt", fstream::in);
	int vertices = 0;
	int edges = 0;
	unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>> edge_map;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> vertices;
		ss >> edges;
		edge_map.rehash(edges);
		int u;
		int v;
		int length;
		while (getline(myfile, line)) {
			stringstream ss(line);
			ss >> u;
			ss >> v;
			ss >> length;
			pair<int, int> temp(u, v);
			edge_map.insert(make_pair(temp, length));
		}
		myfile.close();
	}
	vector<vector<vector<int>>> dp_arr((vertices + 1));
	for (int i = 0; i < dp_arr.size(); i++) {
		dp_arr[i].resize((vertices + 1));
		for (int j = 0; j < dp_arr[i].size(); j++) {
			dp_arr[i][j].resize(2);
		}
	}
	for (int u = 1; u <= vertices; u++) {
		for (int v = 1; v <= vertices; v++) {
			if (u == v) {
				dp_arr[u][v][0] = 0;
			}
			else {
				auto it = edge_map.find(make_pair(u, v));
				if (it != edge_map.end()) {//reachable by one edge
					dp_arr[u][v][0] = it->second;
				}
				else {//not reachable
					dp_arr[u][v][0] = 999999999;
				}
			}
		}
	}
	int currk = 1;
	int prevk = 0;
	for (int k = 1; k <= vertices; k++) {
		//cout << "prevk = " << prevk << ", currk = " << currk << endl;
		for (int u = 1; u <= vertices; u++) {
			for (int v = 1; v <= vertices; v++) {
				int case1 = dp_arr[u][v][prevk];
				int case2 = dp_arr[u][k][prevk] + dp_arr[k][v][prevk];
				//cout << "u = " << u<< ", v = " << v << endl;
				//cout << "value of case 1 = " << case1 << ", case 2 = " << case2 << ", k = " << k << endl;
				int chosen = min(case2, case1);
				//cout << "value chosen = " << chosen << endl;
				dp_arr[u][v][currk] = chosen;

			}
		}
		currk = prevk;
		prevk = !prevk;
	}
	int min = 999999;
	int k = vertices % 2;
	//cout << "value of k = " << k << endl;
	for (int u = 1; u <= vertices; u++) {
		for (int v = 1; v <= vertices; v++) {
			if (u == v && dp_arr[u][v][k] < 0) {
				cout << "value of u = " << u << ", value of v = " << v << endl;
				goto NEGATIVE_CYCLE;
			}
			else if (dp_arr[u][v][k] < min) {
				min = dp_arr[u][v][k];
			}
		}
	}
	/*cout << "size of edge_map =" << edge_map.size() << endl;
	unordered_map <string, int> dp_map;
	for (int u = 1; u <= vertices; u++) {
		for (int v = 1; v <= vertices; v++) {
			floyd_warshall_recurse(dp_map, edge_map, u, v, vertices);
		}
	}
	cout << "size of dp_map = " << dp_map.size() << endl;
	//find the minimum value by looking through dp_map solutions*/
	cout << "minimum distance = " << min << endl;
	return 0;
NEGATIVE_CYCLE: cout << "There is a negative cycle" << endl;
	return 0;
}
int min(int left, int right) {
	return left < right ? left : right;
}
/* Recursive top down approach in this case does not actually save any computations as in the knapsack case.
Reverting to iterative approach where spacing saving is more obvious by removing keeping track of only the previous K -1 cases

void floyd_warshall_recurse (unordered_map<string, int>& dp_map, unordered_map<pair<int, int>, int, boost::hash<pair<int, int>>> & edge_map, int u, int v, int k) {
	string base_key;
	base_key += to_string(u);
	base_key += to_string(v);
	base_key += to_string(k);
	//base cases
	if (u == v && k == 0) {//same vertex
		dp_map.insert(make_pair(base_key, 0));
		return;
	}
	if (u != v && k ==0) {
		auto it = edge_map.find(make_pair(u, v));
		if (it != edge_map.end()) {//reachable by one edge
			dp_map.insert(make_pair(base_key, it->second));
			return;
		}
		else {//not reachable
			dp_map.insert(make_pair(base_key, 9999999));
			return;
		}
	}
	//Recursive calls
	string key_u_v;
	key_u_v += to_string(u);
	key_u_v += to_string(v);
	key_u_v += to_string(k - 1);
	auto it_u_v = dp_map.find(key_u_v);
	if (it_u_v == dp_map.end()) {
		floyd_warshall_recurse(dp_map, edge_map, u, v, k - 1);
		it_u_v = dp_map.find(key_u_v);
	}
	int case1 = it_u_v->second;
	string key_u_k;
	key_u_k += to_string(u);
	key_u_k += to_string(k);
	key_u_k += to_string(k-1);
	auto it_i = dp_map.find(key_u_k);
	if (it_i == dp_map.end()) {
		floyd_warshall_recurse(dp_map, edge_map, u, k, k - 1);
		it_i = dp_map.find(key_u_k);
	}
	string key_k_v;
	key_k_v += to_string(k);
	key_k_v += to_string(v);
	key_k_v += to_string(k - 1);
	auto it_j = dp_map.find(key_k_v);
	if (it_j == dp_map.end()) {
		floyd_warshall_recurse(dp_map, edge_map, k, v, k - 1);
		it_j = dp_map.find(key_k_v);
	}
	int case2 = it_j->second + it_i->second;
	dp_map.insert(make_pair(base_key, min(case2, case1)));
	dp_map.erase(it_j);
	dp_map.erase(it_i);
	dp_map.erase(it_u_v);
	return;
}*/
