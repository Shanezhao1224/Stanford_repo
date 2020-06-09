#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>

using namespace std;

int random_mincut(vector<vector<int>>& vertex_arr);

//The goal of the code is to count the number of inversions in an given array of size 100000
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\Documents\\adjacency_list_input.txt", fstream::in);
	//myfile.open("C:\\Users\\Xzhao\\Documents\\graph_test_input.txt", fstream::in);
	vector<vector<int>> vertex_arr;
	int i = 0;
	//first populate the array with the values inside the text file
	if (myfile.is_open()) {
		int i = 0;
		while (getline(myfile, line)) {//loop through input file
			stringstream stream(line);
			int n;
			bool start = 1;
			vector<int> empty;
			vertex_arr.push_back(empty);
			while (stream >> n) { //loop through the line 
				if (start == 1) {
					start = 0;
					continue;
				}
				vertex_arr[i].push_back(n);
			}
			i++;
		}
		myfile.close();
	}
	
	/*for (int i = 0; i < vertex_arr.size(); i++) {
		cout << i << "th element" << endl;
		for (int j = 0; j < vertex_arr[i].size();j++) {
			cout << "points to vertex " << vertex_arr[i][j] << endl;
		}
	}*/
	int min = 1000;
	//change the seeds per loop?
	srand(100);
	int temp;
	//make a copy to pass to the function to edit in place
	for (int i = 0; i < pow(vertex_arr.size(),2) * log(vertex_arr.size()); i++) {
		vector<vector<int>> pass_vertexarr = vertex_arr;
		temp = random_mincut(pass_vertexarr);
		if (temp < min) min = temp;
		if (i % 10000 == 0) {
			cout << "finished loop i =" << i << endl;
		}
	}
	cout << "mincut = " << min;
}

int random_mincut(vector<vector<int>>& vertex_arr) {
	if (vertex_arr.size() <= 2) {
		return vertex_arr[0].size();
	}
	/*for (int i = 0; i < vertex_arr.size(); i++) {
		cout << i << "th element" << endl;
		for (int j = 0; j < vertex_arr[i].size(); j++) {
			cout << "points to vertex " << vertex_arr[i][j] << endl;
		}
	}*/
	//i = index of vertex a
	int i = rand() % vertex_arr.size();
	//pick vertex b by randomly choosing an edge from vertex a
	int j = rand() % vertex_arr[i].size();
	//j = vertex b, the index of vertex b = vertex b - 1
	j = vertex_arr[i][j] ;
	//cout << "index i = " << i << ", vertex j=" << j << endl;
	//add the edges of vertex b to vertex a
	/*for (int k = 0; k < vertex_arr[j-1].size(); k++) { //worst case O(m)
		vertex_arr[i].push_back(vertex_arr[j-1][k]);
	}*/
	vertex_arr[i].insert(vertex_arr[i].end(), vertex_arr[j - 1].begin(), vertex_arr[j - 1].end());
	//remove self loops
	for (int k = 0; k < vertex_arr[i].size(); k++) { //O(m) at worst generally much less
		if (vertex_arr[i][k] == i+1 || vertex_arr[i][k] == j) {
			vertex_arr[i].erase(vertex_arr[i].begin() + k);
			k--;
		}
	}
	//delete vertex b from the vertex list
	vertex_arr.erase(vertex_arr.begin() + j-1);
	//shift all the pointers
	for (int v = 0; v < vertex_arr.size(); v++) { //O(2m) 
		for (int m = 0; m < vertex_arr[v].size(); m++) {
			//first set edges pointing to 'deleted' node to the 'merged' node
			if (vertex_arr[v][m] == j) vertex_arr[v][m] = i+1;
			//since we deleted a node all the pointers that pointed above the deleted node needs to be shifted down 1
			if (vertex_arr[v][m] > j) vertex_arr[v][m]--;
		}
	}
	//cout << "finished one loop" << endl;
	//recursively call itself
	return random_mincut(vertex_arr); //n-2 recursive calls
}