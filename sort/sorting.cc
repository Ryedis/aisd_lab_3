#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

namespace sort {
	struct stats {
		size_t comparison_count = 0;
		size_t copy_count = 0;
		stats() : comparison_count(0), copy_count(0) {}
		stats(const stats& other) {
			comparison_count = other.comparison_count;
			copy_count = other.copy_count;
		}
		stats& operator=(const stats& other) {
			comparison_count = other.comparison_count;
			copy_count = other.copy_count;
		}
	};

	stats insert_sort(vector<int>& arr) {
		stats stats;
		for (int i = 1; i < arr.size(); i++) {
			for (int j = i; j > 0; j--) {
				stats.comparison_count++;
				if (arr[j - 1] > arr[j]) {
					swap(arr[j - 1], arr[j]);
					stats.copy_count += 2;
				}
			}
		}
		return stats;
	}

	stats shell_sort(vector<int>& arr) {
		stats stat;
		size_t size = arr.size();
		for (size_t d = size / 2; d > 0; d /= 2) {
			for (size_t i = d; i < size; i++) {
				int value = arr[i];
				size_t index = i;
				stat.comparison_count += 1;
				while ((index >= d) && (arr[index - d] > value)) {
					stat.comparison_count += 1;
					arr[index] = arr[index - d];
					stat.copy_count += 1;
					index -= d;
				}
				arr[index] = value;
			}
		}
		return stat;
	}

	stats pyramid_sort(vector<int>& arr) {
		stats stat;
		stat.comparison_count = 0;
		stat.copy_count = 0;
		int n = arr.size();
		for (int i = n / 2 - 1; i >= 0; --i)
			pyramid(arr, n, i, stat);
		for (int i = n - 1; i >= 0; --i) {
			swap(arr[0], arr[i], stat);
			++stat.copy_count;
			pyramid(arr, i, 0, stat);
		}
		return stat;
	}
	
	void pyramid(vector<int>& arr, int n, int i, stats& stats) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left < n && ++stats.comparison_count && arr[left] > arr[largest])
			largest = left;
		if (right < n && ++stats.comparison_count && arr[right] > arr[largest])
			largest = right;
		if (largest != i) {
			swap(arr[i], arr[largest], stats);
			++stats.copy_count;
			pyramid(arr, n, largest, stats);
		}
	}

	void swap(int& a, int& b, stats& stats) {
		int temp = a;
		a = b;
		b = temp;
		stats.copy_count += 3;
	}
















}