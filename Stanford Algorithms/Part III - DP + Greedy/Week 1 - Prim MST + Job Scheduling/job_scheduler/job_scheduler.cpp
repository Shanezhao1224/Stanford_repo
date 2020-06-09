#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>


#define optimal

using namespace std;
int quicksort(vector<pair<unsigned,unsigned>>& myarr, int start, int end);
int partition(vector<pair<unsigned, unsigned>>& myarr, int index, int start, int end);
int choosepivot3(vector<pair<unsigned, unsigned>>& myarr, int start, int end);

//The goal is to implement the greedy algorithm minimizing weight-length. This algorithm is not optimal!
int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\jobs.txt", fstream::in);
	//using an array implementation because O(nt is too slow) for map usage
	vector<pair<unsigned,unsigned>> myarr;
	if (myfile.is_open()) {
		unsigned weight;
		unsigned length;
		double key;
		getline(myfile, line);		//skip the first line
		while (getline(myfile, line)) {//loop through input file line by line
			stringstream stream(line);
			stream >> weight;
			stream >> length;
			pair<unsigned, unsigned> temp(weight, length);
			myarr.push_back(temp);
		}
		myfile.close();
	}
	/*for (int i = 0; i < myarr.size(); i++) {

		cout << "weight[" << i << "] = " << myarr[i].first << ", length[" << i << "] = " << myarr[i].second << endl;
	}*/
	//sort the array by the greedy factor chosen
	quicksort(myarr, 0, myarr.size()-1);
	cout << "value of size = "<<myarr.size() << endl;
	/*for (int i = 0; i < myarr.size() - 1; i++) {

		cout << "weight["<<i<<"] = " << myarr[i].first << ", length["<<i<<"] = " << myarr[i].second << endl;
	}*/
	for (int i = 0; i < myarr.size() -1; i++) {
#ifdef optimal
		double ratio_i;
		double ratio_i2;
		ratio_i = (double)myarr[i].first / (double)myarr[i].second;
		ratio_i2 = (double)myarr[i+1].first / (double)myarr[i+1].second;
		if (ratio_i < ratio_i2) {
			cout << "Error encounter i = " << i << endl;
			cout << "weight[i] = " << myarr[i].first << ", length[i] = " << myarr[i].second << endl;
			cout << "weight[i+1] = " << myarr[i + 1].first << ", length[i+1] = " << myarr[i + 1].second << endl;
		}
#else
		int ratio_i;
		int ratio_i2;
		//weight - length of i
		ratio_i = myarr[i].first - myarr[i].second;
		//weight - length of i +1
		ratio_i2 = myarr[i+1].first - myarr[i+1].second;
		//check that the array is sorted correctly, mainly each job scheduled should be scheduled from descending (weight - length)
		if (ratio_i == ratio_i2) {
			if (myarr[i].first < myarr[i + 1].first) {
				cout << "Error encounter i = " << i << endl;
				cout << "weight[i] = " << myarr[i].first << ", length[i] = " << myarr[i].second << endl;
				cout << "weight[i+1] = " << myarr[i + 1].first << ", length[i+1] = " << myarr[i + 1].second << endl;
			}
		}
		else if (ratio_i < ratio_i2) {
			cout << "Error encounter i = " << i << endl;
			cout << "weight[i] = " << myarr[i].first << ", length[i] = " << myarr[i].second << endl;
			cout << "weight[i+1] = " << myarr[i + 1].first << ", length[i+1] = " << myarr[i + 1].second << endl;
		}
		
#endif
	}
	long long  count = 0;
	long long  time = 0;
	for (int i = 0; i < myarr.size(); i++) {

		time += myarr[i].second;
		count += myarr[i].first * time;
	}
	cout << "value of sum = " << count << endl;

}
int quicksort(vector<pair<unsigned, unsigned>>& myarr, int start, int end) {
	if (start >= end) {
		return 0;
	}
	int count = end - start; //this is to count the number of comparisons down in partition
	int index;
	index = choosepivot3(myarr, start, end);
	int pivotpoint = partition(myarr, index, start, end);
	count += quicksort(myarr, start, pivotpoint - 1);
	count += quicksort(myarr, pivotpoint + 1, end);
	return count;
}
int partition(vector<pair<unsigned, unsigned>>& myarr, int index, int start, int end) {
	if (index != start) {
		swap(myarr[start], myarr[index]);
	}
	
	int i = start + 1;

	for (int j = start + 1; j <= end; j++) {

#ifdef optimal
		double ratio_j;
		double ratio_pivot;
		ratio_j = (double)myarr[j].first / (double)myarr[j].second;
		ratio_pivot = (double)myarr[start].first / (double)myarr[start].second;
		if (ratio_j > ratio_pivot) {
			swap(myarr[j], myarr[i]);
			i++;
		}

#else
		int ratio_j;
		int ratio_pivot;
		ratio_j = myarr[j].first - myarr[j].second;
		ratio_pivot = myarr[start].first - myarr[start].second;
		if (ratio_j > ratio_pivot) {
			swap(myarr[j], myarr[i]);
			i++;
		}
		else if (ratio_j == ratio_pivot) {
			if (myarr[j].first > myarr[start].first) {//we schedule those with a higher weight first
				swap(myarr[j], myarr[i]);
				i++;
			}
		}
#endif
	}
	swap(myarr[start], myarr[i - 1]);
	return i - 1;
}
//randomly choose pivot
int choosepivot3(vector<pair<unsigned, unsigned>>& myarr, int start, int end) {
	int middle = ((start + end) / 2);
	if (middle == start) return start;
	if (myarr[start] > myarr[end]) {
		if (myarr[start] < myarr[middle]) {
			return start;
		}
		else if (myarr[end] > myarr[middle]) {
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




