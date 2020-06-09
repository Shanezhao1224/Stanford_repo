

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

class heap
{

vector<int> heap_data;
void heapify(int index);

public:

	int getmin();
	void insert(int distance);

	int extractmin();

	heap(vector<int> start_distance) {
		heap_data = start_distance;
		int index = heap_data.size()/2 -1;
		while (index >=0) {
			heapify(index);
			index--;
		}
	}
	void changevalue(unsigned index, unsigned value);

};

