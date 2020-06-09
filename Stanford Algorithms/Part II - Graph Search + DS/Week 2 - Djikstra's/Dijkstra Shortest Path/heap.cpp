#include "heap.h"

void heap::insert(int distance) {

	heap_data.push_back(distance);
	int index = heap_data.size() - 1;
	//bubble up
	int parent = ceil((index / 2) - 1);
	while (heap_data[index] > heap_data[parent] && index >0) {
		swap(heap_data[index], heap_data[ceil(index / 2) - 1]);
		index = parent;
		parent = ceil((index / 2) - 1);
	}
	return;
}
int heap::getmin() {
	return heap_data[0];
}

int heap::extractmin() {
	//get the minimum value
	int temp = heap_data[0];
	swap(heap_data[0], heap_data[heap_data.size()-1]);
	heap_data.erase(heap_data.begin() + heap_data.size() - 1);
	int index = 0;
	int child1 = index * 2 + 1;
	int child2 = index * 2 + 2;
	int smallest = index;
	//bubble down
	while (index < heap_data.size()) {
		index = smallest;
		child1 = index * 2 + 1;
		child2 = index * 2 + 2;
		if (child1 < heap_data.size() && heap_data[index] > heap_data[child2]) {
			smallest = child2;
		}
		if (child2 < heap_data.size() && heap_data[smallest] > heap_data[child1]){
			smallest = child1;
		}
		if (smallest == index) {
			break;
		}
		swap(heap_data[smallest], heap_data[index]);
	}
	return temp;
}
void heap::heapify(int index) {
	int child1 = index * 2 + 1;
	int child2 = index * 2 + 2;
	int smallest = index;
	if (child1<heap_data.size() && heap_data[child1] < heap_data[index]) {
		smallest = child1;
	}
	if (child2 < heap_data.size() && heap_data[child2] < heap_data[smallest]) {
		smallest = child2;
	}
	
	if (index != smallest) {
		swap(heap_data[smallest], heap_data[index]);
		heapify(smallest);
	}
	return;
}
void heap::changevalue(unsigned index, unsigned value) {
	int child1 = index * 2 + 1;
	int child2 = index * 2 + 2;
	int smallest = index;
	if (child1 < heap_data.size() && heap_data[child1] < heap_data[index]) {
		smallest = child1;
	}
	if (child2 < heap_data.size() && heap_data[child2] < heap_data[smallest]) {
		smallest = child2;
	}

	if (index != smallest) {
		swap(heap_data[smallest], heap_data[index]);
		heapify(smallest);
	}
	return;
}
