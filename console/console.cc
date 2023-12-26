#include <sort/sort.h>
#include <iostream>
#include <vector>


using namespace sort;
using namespace std;

int main() {
	vector<int> a{ 31, 2, 30, 18, 34, 17, 30, 9, 30, 11, 4, 14, 29, 5, 21, 15, 17, 35, 37, 26, 38, 30, 40, 17, 29, 21, 7, 19, 38, 16 };
	stats b = shell_sort(a);
	cout << a;
	cout << b;
	return 0;
}
