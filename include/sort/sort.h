#pragma once
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
			return *this;
		}
	};

	stats insert_sort(vector<int>& arr) {
		stats stats;
		for (int i = 1; i < arr.size(); i++) {
			for (int j = i; j > 0; j--) {
				stats.comparison_count++;
				if (arr[j - 1] > arr[j]) {
					swap(arr[j - 1], arr[j]);
					stats.copy_count += 3;
				}
			}
		}
		return stats;
	}

	stats shell_sort(vector<int>& arr) {
		stats stats;
		size_t size = arr.size();
		for (size_t d = size / 2; d > 0; d /= 2) {
			for (size_t i = d; i < size; i++) {
				int value = arr[i];
				size_t index = i;
				stats.comparison_count += 1;
				while ((index >= d) && (arr[index - d] > value)) {
					stats.comparison_count += 1;
					arr[index] = arr[index - d];
					stats.copy_count += 1;
					index -= d;
				}
				arr[index] = value;
			}
		}
		return stats;
	}

	void pyramid(vector<int>& arr, size_t n, int i, stats& stats) {
		int largest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;
		if (left < n && ++stats.comparison_count && arr[left] > arr[largest])
			largest = left;
		if (right < n && ++stats.comparison_count && arr[right] > arr[largest])
			largest = right;
		if (largest != i) {
			swap(arr[i], arr[largest]);
			stats.copy_count += 3;
			pyramid(arr, n, largest, stats);
		}
	}

	stats pyramid_sort(vector<int>& arr) {
		stats stat;
		size_t n = arr.size();
		for (int i = n / 2 - 1; i >= 0; --i)
			pyramid(arr, n, i, stat);
		for (int i = n - 1; i >= 0; --i) {
			swap(arr[0], arr[i]);
			stat.copy_count += 3;
			pyramid(arr, i, 0, stat);
		}
		return stat;
	}

	ostream& operator << (ostream& os, const vector<int> vec) {
		os << "{ ";
		for (int i = 0; i < vec.size(); i++) {
			if (i < vec.size() - 1)
				os << vec[i] << ", ";
			else {
				os << vec[i] << " }" << endl;
			}
		}
		return os;
	}

	ostream& operator <<(ostream& os, const stats description) {
		os << "Compasion count: " << description.comparison_count << "; " << "Copy count: " << description.copy_count << endl;
		return os;
	}














}