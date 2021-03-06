// IntersectionUsingHash.cpp : Defines the entry point for the console application.
//

//Intersection of arrays with O(n) space and time complexity
#include "stdafx.h"
#include <iostream>
#include <vector>
using namespace std;
const int TABLE_SIZE = 128;
class HashEntry
{
public:
	int key;
	std::vector<int> listValues;
	HashEntry(int key, int value)
	{
		this->key = key;
		this->listValues.push_back(value);
	}
};

/*
* HashMap Class Declaration
*/
class HashMap
{
private:
	HashEntry * *table;
public:
	HashMap()
	{
		table = new HashEntry *[TABLE_SIZE];
		for (int i = 0; i< TABLE_SIZE; i++)
		{
			table[i] = NULL;
		}
	}
	/*
	* Hash Function
	*/
	int HashFunc(int key)
	{
		return key % TABLE_SIZE;
	}
	/*
	* Insert Element at a key
	*/
	void Insert(int value)
	{
		int hash = HashFunc(value);
		if (table[hash] == NULL)
		{
			table[hash] = new HashEntry(hash, value);
		}
		if (table[hash] != NULL)
			table[hash]->listValues.push_back(value);

	}
	/*
	* Search Element at a key
	*/
	bool Search(int value)
	{
		int  hash = HashFunc(value);
		if (table[hash] != NULL)
		{
			for (auto val : table[hash]->listValues)
				if (val == value)
					return true;

		}
		if (table[hash] == NULL)
			return false;
		return false;
	}
};
class Solution {
public:

	vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
		vector<int> result;
		HashMap hash;
		if (nums1.size() == 0 || nums2.size() == 0)
			return result;
		if (nums1.size()>nums2.size())
		{
			createHashEntry(nums1, hash);
			return formIntersection(nums2, hash);
		}
		else {
			createHashEntry(nums2, hash);
			return formIntersection(nums1, hash);
		}


	}
	void createHashEntry(vector<int> in, HashMap hash) {
		for (auto i : in) {
			hash.Insert(i);
		}
		return;
	}
	vector<int> formIntersection(vector<int> in, HashMap hash) {
		vector<int> result1;
		for (auto i : in) {
			if (hash.Search(i))
			{
				if (std::find(result1.begin(), result1.end(), i) == result1.end())
					result1.push_back(i);
			}
		}
		return result1;
	}



};
//Tes Cases
void display(std::vector<int> v,bool to)
{
	if (v.size() == 0)
		return;
	if (to)
		std::cout << "\n Intersection of two Arrays\n";
	else
		std::cout << "\n Array 1 and Array 2\n";
	for (auto i : v)
		std::cout << i << "\t";
}
int main()
{
	Solution s1;
	HashMap hash;
	std::vector<std::vector<int>> v1;
	
	v1 = { {1,2,3},{2,2},{1,2,3,4,9},{},{},{9},{1,2,3},{4,5} };
	for (int i = 0; i < v1.size()-1;i++) {
		std::vector<int> v;
		display(v1[i], false);
		display(v1[i+1], false);
		v = s1.intersection(v1[i], v1[i + 1]);
		display(v,true);
	}
	return 0;
}

