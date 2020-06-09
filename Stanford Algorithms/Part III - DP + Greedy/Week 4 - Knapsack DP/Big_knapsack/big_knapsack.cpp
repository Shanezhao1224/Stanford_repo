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

int max(int left, int right);

void knapsack_recurse(unordered_map<pair<int, int>, long long, boost::hash<pair<int, int>>> & dp_map, vector<pair<int, int>>& myknapsack, int nindex, int maxweight);

//The goal is given an 'knapsack' constrained by size, compute the maximum value possible by picking the items in the knapsack that fit within size
//The input is a list of items with value and size
//Output the maximum value 
//The difference now is that the input is too big to just iteratively solve all the weights and elements from a naive bottom up approach

/***The current idea is to recursively solve the problem, this should reduce the number of subproblems, and store specific subproblems in a hashmap for lookup
A[n,weight] = max(A[n-1,weight] , A[n-1,weight-Wn])
basically no need to calculate every weight, only the specific weight additions of elements are considered
hashmap will contain key of (n,weight) and the value correspondingly
*/
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\knapsack_big.txt", fstream::in);
	int n = 0;
	int size = 0;
	int i = 0;
	vector<pair<int, int>> myknapsack;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> size;
		ss >> n;
		myknapsack.resize(n);
		while (getline(myfile, line)) {
			stringstream ss(line);
			int value;
			ss >> value;
			int itemsize;
			ss >> itemsize;
			pair<int, int> temp(value, itemsize);
			myknapsack[i] = temp;
			i++;
		}
		myfile.close();
	}
	//this map will store the values of calculations already completed
	unordered_map<pair<int, int>, long long, boost::hash<pair<int,int>>> dp_map; 
	knapsack_recurse(dp_map, myknapsack, n - 1, size);
	auto it = dp_map.find(make_pair(n - 1, size));
	if (it == dp_map.end()) cout << "ERROR value not calculate" << endl;
	cout << "max value = " << it->second << endl;
	cout << "number of subproblems solved = " << dp_map.size() << endl;

}
int max(long long left, long long right) {
	return left > right ? left : right;
}
void knapsack_recurse(unordered_map<pair<int, int>, long long, boost::hash<pair<int, int>>>& dp_map, vector<pair<int, int>>& myknapsack, int nindex, int maxweight) {
	//base case of 0 elements or weight less than 0 
	if (nindex < 0 ) {
		pair<int, int> temp(0, maxweight);
		dp_map.insert(make_pair(temp, 0));
		return;
	}
	long long case1;
	long long case2;
	//find case 1
	auto it = dp_map.find(make_pair(nindex - 1, maxweight));
	if (it == dp_map.end()) {
		knapsack_recurse(dp_map, myknapsack, nindex - 1, maxweight);
		it = dp_map.find(make_pair(nindex - 1, maxweight));
	}
	case1 = it->second;
	//case 1 chosen
	if (maxweight - myknapsack[nindex].second <= 0) {
		pair<int, int> temp(nindex, maxweight); 
		dp_map.insert(make_pair(temp, case1));
		return;
	}
	//case2
	else {
		//find case2
		auto it_2 = dp_map.find(make_pair(nindex - 1, maxweight-myknapsack[nindex].second));
		if (it_2 == dp_map.end()) {
			knapsack_recurse(dp_map, myknapsack, nindex - 1, maxweight - myknapsack[nindex].second);
			it_2 = dp_map.find(make_pair(nindex - 1, maxweight - myknapsack[nindex].second));
		}
		case2 = it_2->second + myknapsack[nindex].first;
		pair<int, int> temp(nindex, maxweight);
		dp_map.insert(make_pair(temp,max(case1, case2)));
		return;
	}
}
