#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility>

using namespace std;

int max(int left, int right);

//The goal is given an 'knapsack' constrained by size, compute the maximum value possible by picking the items in the knapsack that fit within size
//The input is a list of items with value and size
//Output the maximum value 
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\knapsack_small_testcases.txt", fstream::in);
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
	//initialize the 2-d array over n elements and size
	vector<vector<int>> dp_arr;
	dp_arr.resize(n+1);
	for (int i = 0; i < dp_arr.size(); i++) {
		dp_arr[i].resize(size+1);
	}
	//initialize solution with 0 elements to be0
	for (int j = 0; j < size; j++) {
		dp_arr[1][j] = 0;
	}
	//initialize solution with 0 weight to be 0
	for (int i = 0; i < n; i++) {
		dp_arr[i][0] = 0;
	}
	//loop over the dp arr and solve problems up to n and weight w
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= size; j++) {
			int prevweight = j - myknapsack[i-1].second;
			//choose either the same choice as the previous weight (i.e not include current item, or include current item with the optimal value of i-1 and weight - Wi)
			if (prevweight < 0) {
				dp_arr[i][j] = dp_arr[i - 1][j];
			}
			else {
				dp_arr[i][j] = max(dp_arr[i - 1][j], dp_arr[i - 1][prevweight] + myknapsack[i-1].first);
			}	
		}
	}
	cout << "maximum value = " << dp_arr[n][size] << endl;

}
int max(int left, int right) {
	return left > right ? left : right;
}

