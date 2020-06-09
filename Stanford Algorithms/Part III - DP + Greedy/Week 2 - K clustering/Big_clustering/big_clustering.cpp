#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <queue>
#include <functional>
#include <unordered_map>

using namespace std;
//#define naive


int find(vector<pair<int, int>>& union_ds, int index);
void union_op(vector<pair<int, int>>& union_ds, int index_a, int index_b);

//The goal of the code given a very large clustering represented by bits, find the largest k with a min spacing of 3
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\clustering_big.txt", fstream::in);
	//myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\big_cluster_test.txt", fstream::in); 

	int n = 0;
	int k = 0;
	int count = 0;
	int size = 0;
	//maps the bit string to the index in the union-find ds
	unordered_map <string, int> key_index_map;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> n;
		ss >> k;
		key_index_map.rehash(n);
		int length;
		int index = 0;
		while (getline(myfile, line)) {//loop through input file
			stringstream ss(line);
			string bitstring;
			line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
			//if the key does not exist add it to the map
			if (key_index_map.find(line) == key_index_map.end()) {
				pair<string, int> temp_pair(line, index);
				key_index_map.insert(temp_pair);
				index++;
				size++;
			}
			else {
				//else dont add and count it as being merged into a cluster 
				count++;
			}
		}
		myfile.close();
	}
	cout << "value of size = " << size << endl;
	/*for (auto it = key_index_map.begin(); it != key_index_map.end(); it++) {
		cout << "string = " << it->first << ", index = " << it->second << endl;
	}*/
	//Use same union-find ds as k-clustering algorithm
	vector<pair<int, int>> union_find_vertex(size);
	for (unsigned int i = 0; i < union_find_vertex.size(); i++) {
		//initialize all nodes in the union-find to point to itself and have rank 0
		pair<int, int> temp(i, 0);
		union_find_vertex[i] = temp;
	}
	//iterate through the map for each node
	
	for (auto it = key_index_map.begin(); it != key_index_map.end();it++) {
		string key = it->first;
		int index = it->second;
		//loop through the bit combinations for distance of 1
		for (int i = 0; i < k; i++) {
			string temp = key;
			//flip a bit for a hamming distance of 1;
			if (temp[i] == '0') {
				temp[i] = '1';
			}
			else {
				temp[i] = '0';
			}
			auto findit = key_index_map.find(temp);
			//if found distance is too small, need to merge these nodes into a cluster
			if (findit != key_index_map.end()) {
				if (find(union_find_vertex, index) != find(union_find_vertex, findit->second)) {//no cycle
					count++;
					union_op(union_find_vertex, index, findit->second);
				}
			}
		}
		//loop through bit combinations for distance of 2
		for (int i = 0; i < k - 1; i++) {
			string temp1 = key;
			//flip a bit for a hamming distance of 1;
			if (temp1[i] == '0') {
				temp1[i] = '1';
			}
			else {
				temp1[i] = '0';
			}
			for (int j = i + 1; j < k; j++) {
				string temp2 = temp1;
				//flip second bit for a distance of 2
				if (temp2[j] == '0') {
					temp2[j] = '1';
				}
				else {
					temp2[j] = '0';
				}
				auto findit = key_index_map.find(temp2);
				//if found distance is too small, need to merge these nodes into a cluster
				if (findit != key_index_map.end()) {
					if (find(union_find_vertex, index) != find(union_find_vertex, findit->second)) {//no cycle
						count++;
						union_op(union_find_vertex, index, findit->second);
					}
				}
			}
		}//hamming distance 2 loop
	}//map iteration
	cout << "value of count = " << count << endl;
	cout << "k = " << n - count << endl;
	return 0;
}

//the following is the implementation of lazy union, path compression algorithms
int find(vector<pair<int, int>>& union_ds, int index) {
	if (union_ds[index].first == index) {
		return index;
	}
	else {
		//recursively chain up to parent and path compression on return
		union_ds[index].first = find(union_ds, union_ds[index].first);
		return union_ds[index].first;
	}
}
void union_op(vector<pair<int, int>>& union_ds, int index_a, int index_b) {
	int parent_a = find(union_ds, index_a);
	int parent_b = find(union_ds, index_b);
	//if ranks are equal
	if (union_ds[parent_a].second == union_ds[parent_b].second) {
		//set b to point to a and increment a's rank
		union_ds[parent_b].first = parent_a;
		union_ds[parent_a].second++;
	}
	else if (union_ds[parent_a].second > union_ds[parent_b].second) {
		//set b to point to a
		union_ds[parent_b].first = parent_a;

	}
	else {
		//set a to point to b
		union_ds[parent_a].first = parent_b;
	}
	return;
}



