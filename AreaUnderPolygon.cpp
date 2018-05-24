// MockInterviewQuestion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#define _SCL_SECURE_NO_WARNINGS
struct Rect
{
	size_t width;
	size_t height;
	size_t horizontal1;
	size_t horizontal2;
	bool operator < (const Rect& rhs) const {return  height > rhs.height; }
};
void intitialiseValues(Rect rect[6])
{
	std::vector<int> width6 = { 10,10,10,14,14,18,8 };
	std::vector<int> height = { 5,10,8,5,15,2 };
	std::vector<int> horizontal1 = { 0,4,8,12,16,28 };
	std::vector<int> horizontal2 = { 10,14,18,26,30,36 };
	for (int i = 0; i < 6; i++)
	{
		rect[i].height = height[i];
		rect[i].width = width6[i];
		rect[i].horizontal1 = horizontal1[i];
		rect[i].horizontal2 = horizontal2[i];
	}
	return;
}
bool compare(Rect lhs, Rect rhs) { return lhs.horizontal1 < rhs.horizontal2; }

void display(Rect rectTower[6])
{
	std::cout << "STructure after initialisition\n";
	for (int i = 0; i < 6; i++)
	{
		std::cout << "Structure "<<i<<"\n========================\n";
		std::cout << "Height::" << rectTower[i].height << "\t" << "Width " << rectTower[i].width;
		std::cout << "\n Horizontal 1(" << rectTower[i].horizontal1 << ", " << rectTower[i].horizontal2 << ")\n";
	}
	return;
}

int *helper(Rect rectTower[6], int size,int array[37])
{

	//Get sorted and create array for range based queries
	
	int i = 0;
	for (;i<6;i++)
	{
		for (int j = (rectTower[i].horizontal1); j <= rectTower[i].horizontal2; j++)
			if (j > -1)
			{
				if(array[j]==0)
				array[j] = rectTower[i].height;
			}
	}
	return array;
}

// Node for storing minimum nd maximum value of given range
struct node
{
	int minimum;
	int maximum;
};

// A utility function to get the middle index from corner indexes.
int getMid(int s, int e) { return s + (e - s) / 2; }

/*  A recursive function to get the minimum and maximum value in
a given range of array indexes. The following are parameters
for this function.

st    --> Pointer to segment tree
index --> Index of current node in the segment tree. Initially
0 is passed as root is always at index 0
ss & se  --> Starting and ending indexes of the segment
represented  by current node, i.e., st[index]
qs & qe  --> Starting and ending indexes of query range */
struct node MaxMinUntill(struct node *st, int ss, int se, int qs,
	int qe, int index)
{
	// If segment of this node is a part of given range, then return
	//  the minimum and maximum node of the segment
	struct node tmp, left, right;
	if (qs <= ss && qe >= se)
		return st[index];

	// If segment of this node is outside the given range
	if (se < qs || ss > qe)
	{
		tmp.minimum = INT_MAX;
		tmp.maximum = INT_MIN;
		return tmp;
	}

	// If a part of this segment overlaps with the given range
	int mid = getMid(ss, se);
	left = MaxMinUntill(st, ss, mid, qs, qe, 2 * index + 1);
	right = MaxMinUntill(st, mid + 1, se, qs, qe, 2 * index + 2);
	tmp.minimum = std::min(left.minimum, right.minimum);
	tmp.maximum = std::max(left.maximum, right.maximum);
	return tmp;
}

// Return minimum and maximum of elements in range from index
// qs (quey start) to qe (query end).  It mainly uses
// MaxMinUtill()
int MaxMin(struct node *st, int n, int qs, int qe)
{
	struct node tmp;

	// Check for erroneous input values
	if (qs < 0 || qe > n - 1 || qs > qe)
	{
		printf("Invalid Input");
		tmp.minimum = INT_MIN;
		tmp.minimum = INT_MAX;
		return tmp.minimum;
	}

	return MaxMinUntill(st, 0, n - 1, qs, qe, 0).maximum;
}

// A recursive function that constructs Segment Tree for array[ss..se].
// si is index of current node in segment tree st
void constructSTUtil(int arr[], int ss, int se, struct node *st,int si)
{
	// If there is one element in array, store it in current node of
	// segment tree and return
	if (ss == se)
	{
		st[si].minimum = arr[ss];
		st[si].maximum = arr[ss];
		return;
	}

	// If there are more than one elements, then recur for left and
	// right subtrees and store the minimum and maximum of two values
	// in this node
	int mid = getMid(ss, se);
	constructSTUtil(arr, ss, mid, st, si * 2 + 1);
	constructSTUtil(arr, mid + 1, se, st, si * 2 + 2);

	st[si].minimum = std::min(st[si * 2 + 1].minimum, st[si * 2 + 2].minimum);
	st[si].maximum = std::max(st[si * 2 + 1].maximum, st[si * 2 + 2].maximum);
}

/* Function to construct segment tree from given array. This function
allocates memory for segment tree and calls constructSTUtil() to
fill the allocated memory */
struct node *constructST(int arr[], int n)
{
	// Allocate memory for segment tree

	// Height of segment tree
	int x = (int)(ceil(log2(n)));

	// Maximum size of segment tree
	int max_size = 2 * (int)pow(2, x) - 1;

	struct node *st = new struct node[max_size];

	// Fill the allocated memory st
	constructSTUtil(arr, 0, n - 1, st, 0);

	// Return the constructed segment tree
	return st;
}



//The rect should be sorted by x in ascending order
std::vector<int> getAllIntersection(Rect rectTower[6])
{
	std::vector<int> intersect;
	for (int i = 0; i < 6; i++)
	{
		intersect.push_back(rectTower[i].horizontal1);
		intersect.push_back(rectTower[i].horizontal2);
	}
	std::sort(intersect.begin(), intersect.end());
	return intersect;
}

int getMaxArea(int n,struct node *st,Rect rectTower[6])
{

	std::vector<int> v = getAllIntersection(rectTower);
	int maxarea=0;
	for (int i = 0; i < v.size()-1; i++)
	{
		int naxheight = MaxMin(st, n, v[i]+1, (v[i + 1])-1);
		maxarea = maxarea + naxheight * (v[i + 1] - v[i]);
	}
	
	return maxarea;
}

int main()
{

	Rect rectTower[6];
	intitialiseValues(rectTower);
	//display(rectTower);
	int *array;
	//Sort the structure based on height
	std::sort(rectTower, rectTower + 6);
	std::cout << "After Sorting\n====================\n";
	array = (int *)calloc(37 * sizeof(int),37);
	array = helper(rectTower, 6,array);
	
	//Construct a segment tree 
	struct node *st = constructST(array,37);
	int maxarea = getMaxArea(37, st, rectTower);
	std::cout << "Maximum area computed is " << maxarea<<"\n";
	

    return 0;
}

