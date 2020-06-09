#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <queue>

using namespace std;


//The goal is to find the minimum and maximum length of a huffman encoding
//The input is a list of weights coresponding to each code/word/character to encode
//Output the minimum and maximum length

//Using a struct to represent a node as I build the Huffman tree
struct node {
	bool real = true;
	node* left = NULL;
	node* right = NULL;
};

struct pair_comp {
	bool operator() (pair<long long, node*> const left, pair<long long , node*> const right) {
		
		if (left.first == right.first){
			return left.second > right.second;
		}
		else if (left.first < right.first) {
			return false;
		}
		else {
			return true;
		}
	}
};
void DFS(node* parent, int& min, int& max, int count);
/***This algorithm will use a heap with weight and node *
Sorted by the weight, we will extract the two smallest weights and the node associated and combine them.
The combined weight and the parent of the nodes will be inserted into the heap.
Recursively continue until there is only 2 nodes left in the heap.
Then traverse the tree to find the max and min lengths.
We are keeping track of the index as we create the tree, but technically for this problem it is not needed.
***/
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\huffman.txt", fstream::in);
	int i = 0;
	int size = 0;
	vector<pair<long long, node*>> node_arr;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> size;
		int n = 0;
		node_arr.resize(size);
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream ss(line);
			ss >> n;
			node* temp_node = new node;
			pair<long long, node*> temp(n, temp_node);
			node_arr[i] = temp;
			i++;
		}
		myfile.close();
	}
	//create heap from the array, batched insert is O(n) 
	priority_queue<pair<long long, node*>,vector<pair<long long, node*>>, pair_comp> min_heap(node_arr.begin(), node_arr.end());
	cout << "size of heap = " << min_heap.size() << endl;
	cout << "min = " << min_heap.top().first << endl;
	pair<long long, node*> temp1;
	pair<long long , node*> temp2;
	node* node_temp = NULL;
	while (min_heap.size() > 1) {
		if (min_heap.size() == 3) {
			cout << "reached test case" << endl;
		}
		//get the top two elements
		temp1 = min_heap.top();
		min_heap.pop();
		temp2 = min_heap.top();
		min_heap.pop();
		//create a new node as parent to the two elements
		node_temp = new node;
		node_temp->real = false;
		//set left/right pointers
		node_temp->left = temp1.second;
		node_temp->right = temp2.second;
		//reinsert the parent node into heap
		temp2.first =  temp1.first + temp2.first;
		temp2.second = node_temp;
		min_heap.push(temp2);
	}
	cout <<"minheap size should be 1, actual = "<< min_heap.size() << endl;
	
	int min = 99999;
	int max = 0;
	int count = 0;
	//DFS through the tree to find the minimum and maximum length
	DFS(node_temp, min, max, count);
	cout <<"max length = "<< max << endl;
	cout << "min length = " << min << endl;


}

void DFS(node* parent, int& min, int& max, int count) {
	if (parent->left == NULL && parent->right == NULL) {
		if (parent->real == false) {
			cout << "ERROR! leaf node is false" << endl;
		}
		if (count < min) {
			min = count;
		}
		else if (count > max) {
			max = count;
		}
		return;
	}
	else {
		count++;
		DFS(parent->left, min, max, count);
		DFS(parent->right, min, max, count);
		return;
	}
}

