#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;


/* Implementation of the quick sort algorithm with 3 different pivot choose algorithms
The goal is to count the number of comparisons for each type of pivot choice to get a better understanding of runtime.
*/
int quicksort(vector<int> &myarr, int start, int end);
int partition(vector<int> &myarr, int index, int start, int end);
int choosepivot1(int start);
int choosepivot2(int end);
int choosepivot3(vector<int> &myarr, int start, int end);


int main() {

	//Read in input from text file
	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\Documents\\Quicksort_input.txt", fstream::in);
	vector<int> myarr;
	int i = 0;
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			myarr.push_back(stoi(line));
			i++;
		}
		myfile.close();
	}

	//goal is to count number of comparisons
	cout << quicksort(myarr, 0, myarr.size() - 1) << endl;
	/*for (int i = 0; i < myarr.size(); i++) {
		cout << "value of myarr[" << i << "] = " << myarr[i] << endl;
	}*/

	return 0;
}

int quicksort(vector<int> &myarr, int start, int end) {
	if (start >= end) {
		return 0;
	}
	int count = end-start; //this is to count the number of comparisons down in partition
	int index;
	//index = choosepivot1(start);
	//index = choosepivot2(end);
	index = choosepivot3(myarr, start, end);
	int pivotpoint = partition(myarr, index, start, end);
	count += quicksort(myarr, start, pivotpoint - 1);
	count += quicksort(myarr, pivotpoint + 1, end);
	return count;
}
int partition(vector<int> &myarr, int index, int start, int end) {
	if (index != start) {
		swap(myarr[start], myarr[index]);
	}
	//cout << "value of myarr[0] = " << myarr[0] << endl;
	int i = start +1;
	for (int j = start + 1; j <= end; j++) {
		if (myarr[j] < myarr[start]) {
			swap(myarr[j], myarr[i]);
			i++;
		}
	}
	int temp = myarr[start];
	//cout << "value of myarr[i] =" << myarr[i-1] << endl;
	swap(myarr[start], myarr[i - 1]);
	//cout << "temp = " << temp << ", myarr[temp] = " << myarr[temp-1] << endl;
	//cout << "value of myarr[0] =" << myarr[0] << endl;
	return i - 1;
}
//basic pivot algorithm where you always choose the start most element
int choosepivot1(int start) {
	return start;
}

int choosepivot2(int end) {
	return end;
}
int choosepivot3(vector<int> &myarr, int start, int end) {
	int middle = ((start + end) / 2);
	if (middle == start) return start;
	if (myarr[start] > myarr[end]) {
		if (myarr[start] < myarr[middle]) {
			return start;
		}else if (myarr[end] > myarr[middle]) {
			return end;
		}
		else {
			return middle;
		}
	}
	else { 
		if (myarr[end] < myarr[middle]) {
			return end;
		}
		else if (myarr[start] > myarr[middle]) {
			return start;
		}
		else {
			return middle;
		}
	}
}