#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
#include <unordered_map>

using namespace std;

//The goal is to output the number of distinct pairs of x and y, s.t x + y = t, where t = (-10000,10000)
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\2sum_input.txt", fstream::in);
	//using an array implementation because O(nt is too slow) for map usage
	vector<long long> myarr;
	if (myfile.is_open()) {
		long long n;
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream stream(line);
			stream >> n;
			myarr.push_back(n);
		}
		myfile.close();
	}

	sort(myarr.begin(), myarr.end());
	//remove duplicates, we only care about distinct pairs. Duplicates can cause runtime to hit O(n^2)
	for (int i = 0; i < myarr.size()-1; i++) {
		if (myarr[i] == myarr[i + 1]) {
			myarr.erase(myarr.begin()+i);
			i--;
		}
	}
	int i = 0;
	int j = myarr.size();
	vector<bool> found(20001, false);
	while (i < j) {
		if (myarr[i] + myarr[j] < -10000) {
			i++;
		}
		else if (myarr[i] + myarr[j] > 10000) {
			j--;
		}
		else {
			for (int k = i; k < j; k++) {
				int target = myarr[k] + myarr[j];
				if (target > 10000) {
					break;
				}
				else {
					found[target + 10000] = true;
				}
			}
			i++;
		}
	}
	int count = 0;
	for (int i = 0; i < found.size(); i++) {
		if (found[i]) count++;
	}
	cout << "number of distinct values hit in t = " << count << endl;
}

	


