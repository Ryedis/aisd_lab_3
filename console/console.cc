#include <sort/sort.h>
#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace sort;
using namespace std;

int main() {
	//insert_sort
	//shell_sort
	//pyramid_sort


	//vector<stats> a = sort_hundred_ordered_vectors(1);
	//vector<stats> a = sort_hundred_ordered_vectors(2);
	//vector<stats> a = sort_hundred_ordered_vectors(3);
	
	//vector<stats> a = sort_hundred_random_vectors(1);
	//vector<stats> a = sort_hundred_random_vectors(2);
	//vector<stats> a = sort_hundred_random_vectors(3);
	 
	//vector<stats> a = sort_hundred_reversed_ordered_vectors(1);
	//vector<stats> a = sort_hundred_reversed_ordered_vectors(2);
	vector<stats> a = sort_hundred_reversed_ordered_vectors(3);
	cout << a;
	write_to_file(a, "reversed_ordered_insert_sort.txt");
	return 0;
}
