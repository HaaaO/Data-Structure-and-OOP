#include <string>
#include <iostream>
#include <vector>


// swap helper function
template <class T, class Comparator>
void swap(std::vector<T> &myArray, int a, int b)
{
	T temp = myArray[b];
	myArray[b] = myArray[a];
	myArray[a] = temp;
}

// take the median of the leftmost,rightmost and middle and also sort them
template<class T, class Comparator>
void median_val(std::vector<T> &myArray, int left, int right, Comparator comp){

	if(right-left >= 2){
		int middle = (left+right)/2;
	if(!comp(myArray[left],myArray[right])){
		swap<T, Comparator>(myArray, left, right);
	}
	if(!comp(myArray[middle], myArray[right])){
		swap<T, Comparator>(myArray, middle, right);
	}
	if(!comp(myArray[left], myArray[middle])){
		swap<T, Comparator>(myArray,left,middle);
	}
	swap<T, Comparator>(myArray,middle, right-1);
	}
	else if (right-left ==1){
		if(comp(myArray[left],myArray[right])){
		swap<T, Comparator>(myArray, left, right);
	}
	}
}
	
// Take the partition by using the rightmost element as the pivot
template <class T, class Comparator>
int partition_normal(std::vector<T> &myArray, int l, int r, Comparator comp){
	int i = l;
	T p = myArray[r];
	for (int j = l; j < r; j++){
		if(comp(myArray[j],p)){
			T temp = myArray[i];
			myArray[i] = myArray[j];
			myArray[j] = temp;
			i++;
		}
	}
	T temp = myArray[r];
	myArray[r] = myArray[i];
	myArray[i] = temp;
	return i;
}

// the partition function to call the meidan function and the normal quicksort partition function
template<class T, class Comparator>
int partition(std::vector<T> &myArray, int l, int r, Comparator comp){
		median_val<T, Comparator>(myArray, l , r, comp);
		int left = l +1;
		int right = r -1;
		int val = 0;
		val = partition_normal<T,Comparator>(myArray,left,right,comp);
	    return val;
}

// The helper function to take in left and right index and the comparator
template<class T, class Comparator>
void QuickSort_helper(std::vector<T> &myArray, int l, int r, Comparator comp){
	if(l < r){
		int m = partition(myArray , l , r, comp);
		QuickSort_helper(myArray,l, m-1,comp);
		QuickSort_helper(myArray, m+1, r,comp);
	}
}

// The actual quicksort function 
template<class T, class Comparator>
void QuickSort(std::vector<T> &myArray, Comparator comp){
	QuickSort_helper(myArray, 0, int(myArray.size())-1,comp);
}












