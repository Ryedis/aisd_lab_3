#include "sort/sort.h"
#include <gtest/gtest.h>
#include <iostream>
using namespace std;
using namespace sort;


TEST(SortTests, insert_sort) {
    vector<int> a = { 1, 5, 4, 3, 2, 7, 6 };
    vector<int> b = { 1, 2, 3, 4, 5, 6, 7 };
   
    insert_sort(a);
    EXPECT_EQ(a, b);

}

TEST(SortTests, shell_sort) {
    vector<int> a = { 1, 5, 4, 3, 2, 7, 6 };
    vector<int> b = { 1, 2, 3, 4, 5, 6, 7 };

    shell_sort(a);
    EXPECT_EQ(a, b);

}

TEST(SortTests, pyramid_sort) {
    vector<int> a = { 1, 5, 4, 3, 2, 7, 6 };
    vector<int> b = { 1, 2, 3, 4, 5, 6, 7 };

    pyramid_sort(a);
    EXPECT_EQ(a, b);

}