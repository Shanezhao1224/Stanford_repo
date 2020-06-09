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


//The goal is to find the Maximum weight indepent set of a Graph. 
//Input file is a list of weights for each vertex. 
//Output which of the vertices 1, 2, 3, 4, 17, 117, 517, and 997 are part of the Maximum weight set.
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\mwis.txt", fstream::in);
	vector<int> input_arr;
	int i = 0;
	
	int size = 0;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> size;
		int n = 0;
		input_arr.resize(size);
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream ss(line);
			ss >> n;
			input_arr[i] = n;
			i++;
		}
		myfile.close();
	}
	//initialize the dp_arr
	vector<long long> dp_arr(size, 0);
	dp_arr[0] = input_arr[0];
	dp_arr[1] = input_arr[1];
	//loop through all the inputs and calculate the weight at each position
	for (int i = 2; i < size; i++) {
		int max = input_arr[i] + dp_arr[i - 2];
		dp_arr[i] = max > dp_arr[i - 1] ? max : dp_arr[i - 1];
	}
	//loop backwards to determine if an vertex is part of the maximum weight set
	vector<bool> vertex_bool(size, false);
	i = size - 1;
	while (i >= 2) {
		if (dp_arr[i] > dp_arr[i - 1]) {
			vertex_bool[i] = true;
			vertex_bool[i - 1] = false;
			i = i - 2;
		}
		else {
			vertex_bool[i] = false;
			i--;
		}
	}
	vertex_bool[i] = true;
	int output_arr[8] = {1, 2, 3, 4, 17, 117, 517, 997};
	for (int j = 0; j < 8; j++) {
		cout << "["<<output_arr[j]-1<<"] is "<<vertex_bool[output_arr[j]-1]<<endl;
	}
}



