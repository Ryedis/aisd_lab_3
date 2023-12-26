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
		stats& operator+=(const stats& other) {
			comparison_count += other.comparison_count;
			copy_count += other.copy_count;
			return *this;
		}
		stats& operator/(const int other) {
			comparison_count /= other;
			copy_count /= other;
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

	ostream& operator<<(ostream& os, const vector<stats>& stats_vec) {
		for (const stats& description : stats_vec) {
			os << description << endl;
		}
		return os;
	}

	vector<int> ordered_vector(int n) {
		vector<int> vector;
		for (int i = 1; i <= n; i++) {
			vector.push_back(i);
		}
		return vector;
	}
	vector<int> reversed_ordered_vector(int n) {
		vector<int> vector;
		for (int i = n; i > 0; i--) {
			vector.push_back(i);
		}
		return vector;
	}

	vector<int> random_seed(int a, int b, int n, int seed) {
		vector<int> res;
		mt19937 generator(seed);
		uniform_int_distribution<> distribution(a, b);
		for (int i = 0; i < n; i++) {
			int x = distribution(generator);
			res.push_back(x);
		}
		return res;
	}

	stats sort_random_vector(int length_vector, int trial_count, int sort) {
		stats stat;
		for (int i = 0; i < trial_count; i++) {
			std::vector<int> test = random_seed(-1000, 1000, length_vector, i + 1);
			cout << "iteration: " << i << endl;
			switch (sort) {
			case 1:
				stat += insert_sort(test);
				break;
			case 2:
				stat += shell_sort(test);
				break;
			case 3:
				stat += pyramid_sort(test);
				break;
			}
		}
		stat = stat / trial_count;
		return stat;
	}

	vector<stats> sort_hundred_random_vectors(int sort) {
		vector<stats> stat;
		for (int i = 1; i < 11; i++) {
			cout << "len: " << i * 1000 << endl;
			stat.push_back(sort_random_vector(i * 1000, 100, sort));
		}
		for (int i = 25000; i < 100001; i *= 2) {
			cout << "len: " << i << endl;
			stat.push_back(sort_random_vector(i, 100, sort));
		}
		return stat;
	}

	vector<stats> sort_hundred_ordered_vectors(int sort) {
		vector<stats> stat;
		for (int i = 1; i < 11; i++) {
			cout << "len: " << i * 1000 << endl;
			vector<int> a = ordered_vector(i * 1000);
			switch (sort) {
			case 1:
				stat.push_back(insert_sort(a));
				break;
			case 2:
				stat.push_back(shell_sort(a));
				break;
			case 3:
				stat.push_back(pyramid_sort(a));
				break;
			}
		}

		for (int i = 25000; i < 100001; i *= 2) {
			cout << "len: " << i << endl;
			vector<int> a = ordered_vector(i);
			switch (sort) {
			case 1:
				stat.push_back(insert_sort(a));
				break;
			case 2:
				stat.push_back(shell_sort(a));
				break;
			case 3:
				stat.push_back(pyramid_sort(a));
				break;
			}
		}
		return stat;
	}

	vector<stats> sort_hundred_reversed_ordered_vectors(int sort) {
		vector<stats> stat;
		for (int i = 1; i < 11; i++) {
			cout << "len: " << i * 1000 << endl;
			vector<int> a = reversed_ordered_vector(i * 1000);
			switch (sort) {
			case 1:
				stat.push_back(insert_sort(a));
				break;
			case 2:
				stat.push_back(shell_sort(a));
				break;
			case 3:
				stat.push_back(pyramid_sort(a));
				break;
			}
		}

		for (int i = 25000; i < 100001; i *= 2) {
			cout << "len: " << i << endl;
			vector<int> a = reversed_ordered_vector(i);
			switch (sort) {
			case 1:
				stat.push_back(insert_sort(a));
				break;
			case 2:
				stat.push_back(shell_sort(a));
				break;
			case 3:
				stat.push_back(pyramid_sort(a));
				break;
			}
		}
		return stat;
	}
	void write_to_file(const vector<stats>& stat, const string& name) {
		ofstream out;
		string path = "C:/papka/aisd_lab_3/sort_res/";
		out.open(path + name);
		for (int i = 0; i < stat.size(); i++) {
			out << stat[i].comparison_count << " " << stat[i].copy_count << endl;
		}
		out.close();
	}










}