#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <utility>
#include <functional>
#include <queue>

using namespace std;

//The goal is to sum the median as each integer is read from input stream
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\MedianMaintenace.txt", fstream::in);
	//myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\SCC_test_cases.txt", fstream::in);

	priority_queue <int> max_heap;
	priority_queue <int,vector<int>,greater<int>> min_heap;
	int median = 9999999;
	int count = 0;
	int n;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream ss(line);
			ss >> n;
			if (min_heap.size()-2 == max_heap.size()) {
				if (n > min_heap.top()) {
					max_heap.push(min_heap.top());
					min_heap.pop();
					min_heap.push(n);
				}
				else {
					max_heap.push(n);
				}
			}
			else {
				if (max_heap.size() == 0) {
					min_heap.push(n);
				}
				else if (n > max_heap.top()) {
					min_heap.push(n);
				}
				else {
					min_heap.push(max_heap.top());
					max_heap.pop();
					max_heap.push(n);
					
				}
			}
			count += min_heap.top();
			cout << "median = " << min_heap.top() << endl;
		}
		myfile.close();
	}
	cout << "value of count % 10000 = " << count % 10000 << endl;

}



