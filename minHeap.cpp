#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
class MinHeap
{
	vector <int> heap;
	void heapifyUp(int index)
	{
		if(index == 0)
		{
			return ;
		}
		int parentIndex= (index-1)/2;
		int parent = heap[parentIndex];
		if(parent > heap[index])
		{
			swap(parentIndex, index);
			heapifyUp(parentIndex);
		}
		return ;
	}
	void heapifyDown(int index)
	{
		int leftChildIndex = 2*i+1;
		int rightChildIndex = 2*i+2;

		int smallestIdx= index;
		//case 1: if the new min index is smaller than left and right, do nothing
		if(leftChildIndex < heap.size() && heap[leftChildIndex] < heap[index])
		{
			smallestIdx  = leftChildIndex;
		}


		if(rightChildIndex < heap.size() && heap[rightChildIndex] < heap[index])
		{
			smallestIdx = rightChildIndex;
		}

		if(smallestIdx !=  index)
		{
			swap(heap[index], heap[smallestIdx]);
			heapifyDown(smallestIdx]);
		}

		return ;

		//case 2: if the new min index is greater than right, right is the smallest
		// case 2: same for left


	}

public:
	void insert(int value)
	{
		//whenever we are inserting value, we are inserting in vector
		heap.push_back(value);
		heapifyUp(heap.size()-1);
	}
	int extractMin()
	{
		if(heap.empty())
		{
			return -1;
		}
		int min = heap[0];
		heap[0] = heap.back();
		heap.pop_back();
		if(heap.size() != 1)
		{
			heapifyDown(0);
		}
		

	}
	int peek() const;

}
