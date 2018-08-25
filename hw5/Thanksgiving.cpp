#include <algorithm>
#include <iostream>
#include "LengthMismatch.h"
#include <vector>
#include <string>
#include <functional>



std::vector<std::pair<int, int>> assignPlates(std::vector<int> turkeys, std::vector<int> potatoes) {
	std::less<int> les;
	std::greater<int> lar;
	std::vector<std::pair<int, int>> results;
	std::vector<std::pair<int, int>> results_empty;


	int size_a = int(turkeys.size());
	int size_b = int(potatoes.size());

	LengthMismatch mis(size_a,size_b);
	if(size_a != size_b){
		throw mis;
	}

	if(turkeys.size() == 0 && potatoes.size() == 0){
		results = results_empty;
	}
	else{

		sort(turkeys.begin(),turkeys.end(),les);
	sort(potatoes.begin(), potatoes.end(),lar);


	int total = 0;

	for (int i = 0; i < size_a; i++){
		total = total + turkeys[i] + potatoes[i];

		std::pair<int,int> insert_pair(turkeys[i], potatoes[i]);
		results.push_back(insert_pair);
	}

	bool check = true;
	total = total / size_a;
	int sum;
	for (int i = 0; i < size_a; i++){
		sum = results[i].first + results[i].second;
		if(total != sum){
			check = false;
		}
	}

	if (check == false){
		results = results_empty;
	}

	}
	return results;
	
}













