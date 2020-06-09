#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

unsigned int countinversions(vector <int>& myarr, int start, int end);
int mergecount(vector<int>& myarr, int start1, int end1, int start2, int end2);

//The goal of the code is to count the number of inversions in an given array of size 100000
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\Documents\\int.txt",fstream::in);
	vector<int> myarr;
	int i = 0;
	//first populate the array with the values inside the text file
	if (myfile.is_open()) {
		while (getline(myfile, line)) {//loop through input file
			myarr.push_back(stoi(line));
			i++;
		}
		myfile.close();
	}
	else {
		cout << "file not opened" << endl;
		return 0;
	}

	cout << countinversions(myarr, 0, myarr.size() - 1) << endl;
	/*for (int i = 0; i < myarr.size(); i++) {
		cout << "value of myarr[" << i << "] = " << myarr[i] << endl;
	}*/
	return 0;
}
unsigned int countinversions(vector <int>& myarr, int start, int end) {
	int count = 0;
	if (start == end) {//base case element is just 1
		return 0;
	}
	else {
		int start1 = start;
		int end1 = (start + end)/ 2;
		int start2 = end1 + 1;
		int end2 = end;
		//recurse left
		count += countinversions(myarr, start1, end1);
		//recurse right
		count += countinversions(myarr,start2, end2);
		//merge step and count step
		count += mergecount(myarr, start1, end1, start2, end2);
	}
	return count;
}

int mergecount(vector<int>& myarr, int start1, int end1, int start2, int end2) {
	int count = 0;
	int size1 = end1 - start1 + 1;
	int size2 = end2 - start2 + 1; 
	//create temporary arrays
	int * temparr1 = new int[size1];
	int * temparr2 = new int[size2];
	//cout << "value of start1 = " << start1 << " value of end1 = " << end1 << endl;
	//cout << "value of start2 = " << start2 << " value of end2 = " << end2 << endl;
	//cout << "value of size 1 = " << size1 << " value of size 2 = " << size2 << endl;
	//copy values into temporary arrays
	for (int i = 0; i < size1; i++) {
		temparr1[i] = myarr[i+start1];
	}
	
	for (int i = 0; i < size2; i++) {
		temparr2[i] = myarr[i+start2];
	}
	/*for (int i = 0; i < size1; i++) {
		cout << "value of temparr1[" << i << "] = " << temparr1[i] << endl;
	}

	for (int i = 0; i < size2; i++) {
		cout << "value of temparr2[" << i << "] = " << temparr2[i] << endl;
	}*/
	int i = 0;
	int j = 0;
	int k = start1;
	while (i < size1 && j < size2) {
		if (temparr1[i] > temparr2[j]) {
			myarr[k] = temparr2[j];
			j++;
			count+= size1 - i;
			//cout << "count incremented by " << size1 - i << endl;
		}
		else {
			myarr[k] = temparr1[i];
			i++;
		}
		k++;
	}
	if (i < size1) {
		while (i < size1) {
			myarr[k] = temparr1[i];
			i++;
			k++;
		}
	}
	else if (j < size2) {
		while (j < size2) {
			myarr[k] = temparr2[j];
			j++;
			k++;
		}
	}
	delete [] temparr1;
	delete [] temparr2;
	return count;
}

