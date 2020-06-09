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

struct vertex {
	float x;
	float y;
};
void find_min(int size, const vector<vertex>& vertex_arr, unordered_map<pair<string, int>,float,boost::hash<pair<string, int>>>& dp_map_0,
	unordered_map<pair<string,int>, float, boost::hash<pair<string, int>>> & dp_map_1, string key, int start, int loopsize, 
	const unordered_map<pair<int, int>, float, boost::hash<pair<int, int>>>& distance_map);
float euclidean_distance(vertex a, vertex b);
//The goal is given an G with vertices as a set of (x,y) coordinates, solve the TSP
//The input is a list of vertices with its (x,y) coordinates
//Output minimum cost tour rounded to integer

//Going to use the DP O(n^2 * 2^n) algorithm for this small dataset.
//This algorithm is guaranteed to be correct


//Some optimizations for the future, Store the n^2 distances between each edge, so we don't calculate distance each iteration: DONE
//Use a bitwise representation for the sets instead of string. We can store an array of numbers 0 - 2^24. 
//Sort the numbers by number of bits set to 1. Then for each number iterate through which bits are set to determine which vertexes are in the set.

//The maximum number of elements in the hashmap (24 choose 12)*12 + (24 choose 13)*13 is actually still 1/6 of 2^24 * 24. 
//But the maximum size to store the character string, value, and pointers exceeds 24bytes or 6*4bytes of the array. 
//It would be both faster and more space efficient to use an array in this case

int main() {

	string line;
	fstream myfile;
	myfile.open("C:\\Users\\Xzhao\\source\\repos\\Test_inputs\\TSP.txt", fstream::in);
	int n_vertices = 0;
	vector<vertex> vertex_arr;
	if (myfile.is_open()) {
		getline(myfile, line);
		stringstream ss(line);
		ss >> n_vertices;
		vertex_arr.resize(n_vertices);
		float x;
		float y;
		int i = 0;
		while (getline(myfile, line)) {
			stringstream ss(line);
			ss >> x;
			ss >> y;
			vertex_arr[i].x = x;
			vertex_arr[i].y = y;
			i++;
		}
		myfile.close();
	}
	cout << "finished reading input" << endl;
	//create a hashmap with the distances
	unordered_map<pair<int, int>, float, boost::hash<pair<int, int>>> distance_map;
	for (int i = 0; i < n_vertices-1; i++) {
		for (int j = i; j < n_vertices; j++) {
			distance_map.insert(make_pair(make_pair(i,j),euclidean_distance(vertex_arr[i], vertex_arr[j])));
		}
	}
	unordered_map<pair<string,int>, float, boost::hash<pair<string, int>>> dp_map_0;
	unordered_map<pair<string, int>, float, boost::hash<pair<string, int>>> dp_map_1;
	//initialization loop
	string key = "0";
	for (int j = 1; j < n_vertices; j++) {
		string tempkey = key;
		tempkey += char('0' + j);
		pair<string, int> mapkey(tempkey, j);
		pair<int, int> temp(0, j);
		auto it = distance_map.find(temp);
		dp_map_0.insert(make_pair(mapkey, it->second));
	}
	for (int m = 3; m <= n_vertices;m++) { //loop over set size
		cout << "m = " << m << endl;
		float min = 99999999;
		if (m % 2) {
			find_min(m - 1, vertex_arr, dp_map_0, dp_map_1, "0", 1, n_vertices - (m - 1), distance_map);
			cout << "elements of map 0 = " << dp_map_0.size() << endl;
			cout << "elements of map 1 = " << dp_map_1.size() << endl;
			cout << "size of map 0 = " << dp_map_0.bucket_count() << endl;
			cout << "size of map 1 = " << dp_map_1.bucket_count() << endl;
			dp_map_0.clear();
		}
		else {
			find_min(m - 1, vertex_arr, dp_map_1, dp_map_0, "0", 1, n_vertices - (m - 1), distance_map);
			cout << "elements of map 0 = " << dp_map_0.size() << endl;
			cout << "elements of map 1 = " << dp_map_1.size() << endl;
			cout << "size of map 0 = " << dp_map_0.bucket_count() << endl;
			cout << "size of map 1 = " << dp_map_1.bucket_count() << endl;
			dp_map_1.clear();
		}
		
	}
	//loop through the final dp_arr and find the minimum distance
	float min = 999999999999;
	string finalkey = "0";
	//create the total key
	for (int i = 1; i < n_vertices; i++) {
		finalkey += char('0' + i);
	}
	for (int j = 1; j < n_vertices; j++) {
		auto it_dis = distance_map.find(make_pair(0, j));
		float distance = it_dis->second;
		pair<string, int> temp(finalkey, j);
		auto it = dp_map_0.begin();
		if (n_vertices % 2) { 
			it = dp_map_1.find(temp); 
		}
		else { 
			it = dp_map_0.find(temp); 
		}
		distance += it->second;
		if (distance < min) {
			min = distance;
		}
	}
	cout << "minimum tour is = " << min << endl;

}
float euclidean_distance(vertex a, vertex b) {
	return sqrt(pow(abs(a.x - b.x),2) + pow(abs(a.y - b.y), 2));
}
//This recursive patterns determines the the indexes in the set and then loops over the possible destination vertex j in the set
void find_min(int size, const vector<vertex>& vertex_arr, unordered_map<pair<string,int>, float, boost::hash<pair<string, int>>> & dp_map_0, 
	unordered_map<pair<string, int>, float, boost::hash<pair<string, int>>> &dp_map_1, string key, int start, int loopsize, 
	const unordered_map<pair<int, int>, float, boost::hash<pair<int, int>>>& distance_map) {
	size--;
	int index = start;
	for (int i = 0; i < loopsize; i++) {
		string tempkey = key;
		tempkey += char('0' + index);
		if (size > 0) {
			find_min(size, vertex_arr, dp_map_0, dp_map_1, tempkey, index + 1, loopsize -i,distance_map);
		}
		else {//adding the final 'char' to the tempkey to finish the setkey
			int y = 1;
			//loop over the possible destination vertex j 
			int vertex_j;
			//cout << "setkey = " << tempkey << endl;
			while (y < tempkey.size()) {
				float min = 99999999;
				vertex_j = int(tempkey[y] - '0');
				string setkey = tempkey;
				tempkey.erase(tempkey.begin() + y);
				int k = 1;
				int vertex_k;
				//loop over the vertex k 
				while (k < tempkey.size()) {
					vertex_k = int(tempkey[k] - '0');
					pair<string, int> temp(tempkey, vertex_k);
					auto it = dp_map_0.find(temp);
					pair<int, int> dist_key;
					if (vertex_k < vertex_j) {
						dist_key = make_pair(vertex_k, vertex_j);
					}
					else {
						dist_key = make_pair(vertex_j, vertex_k);
					}
					auto dis_it = distance_map.find(dist_key);
					float distance = dis_it->second + it->second;
					if (distance < min) min = distance;
					k++;
				}
				y++;
				tempkey = setkey;
				pair<string, int> temp(tempkey, vertex_j);
				dp_map_1.insert(make_pair(temp, min));
			}
		}
		index++;
	}
	return;
}
